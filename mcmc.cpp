/*
 *  mcmc.cpp
 *  Selection_Recombination
 *
 *  Created by Joshua Schraiber on 5/2/13.
 *  Copyright 2013 UC Berkeley. All rights reserved.
 *
 */

#include "mcmc.h"
#include "MbRandom.h"
#include "settings.h"
#include "path.h"
#include "measure.h"
#include "param.h"
#include <numeric>

#include<iomanip>
#include<fstream>

mcmc::mcmc(settings& mySettings, MbRandom* r) {
	random = r;
	printFreq = mySettings.get_printFreq();
	sampleFreq = mySettings.get_sampleFreq();
	num_gen = mySettings.get_num_gen();
	minUpdate = mySettings.get_grid();
	if (!mySettings.get_linked()) {
		no_linked_sites(mySettings);
	} else {
		
	}
}

void mcmc::no_linked_sites2(settings& mySettings) {
    paramFile.open("results.csv", std::fstream::app);
    paramFile << "todel"<< std::endl;
    paramFile.close();

}

void mcmc::no_linked_sites(settings& mySettings) {

	//open files
	// std::string paramName = mySettings.get_baseName() + ".csv";
	// std::string trajName = mySettings.get_baseName() + ".traj";
	// std::string timeName = mySettings.get_baseName() + ".time";
	
    //paramFile.open(paramName.c_str());
    //std::vector<double> alpha_1_vector;
    //std::vector<double> alpha_2_vector;
	//trajFile.open(trajName.c_str());
	// timeFile.open(timeName.c_str());
	

    std::vector<double> alpha_1_vector;
    std::vector<double> alpha_2_vector;

	//initialize wfMeasure
	wfMeasure* curWF = new wfMeasure(random,0);
	//wfMeasure* oldWF = NULL;
	curWF->set_num_test(mySettings.get_num_test());
		    
    //parse the settings
    popsize* myPop = mySettings.parse_popsize_file();
    std::vector<sample_time*> sample_time_vec = mySettings.parse_input_file(random);
    
    //initialize path
    curPath = new wfSamplePath(sample_time_vec, myPop, curWF, mySettings, random);
	
	param_gamma* alpha1 = new param_gamma(mySettings.get_a1start(),random);
	
	param_gamma* alpha2 = new param_gamma(mySettings.get_a2start(),random);
	
	param_path* curParamPath = new param_path(curPath,alpha1,alpha2,random,mySettings);
    
    param_F* cur_F = new param_F(0.1,random);
    curPath->set_F(cur_F);
    
    start_freq* start;
    param_age* age;
    if (!mySettings.get_infer_age()) {
        start = new start_freq(curPath->get_traj(0),random,curParamPath);
    } else {
        //std::cout << "Proposing first allele age" << std::endl;
        double firstAge = curPath->get_time(0);
        //std::cout << "firstAge is " << firstAge << std::endl;
        age = new param_age(firstAge, random, curParamPath, mySettings.get_dt(), mySettings.get_grid());
        //std::cout << "First allele age is " << age->get() << std::endl;
        curPath->set_update_begin(0);
        curPath->set_old_index(-1);
    }
    

    
	
	//initialize the parameter vector
    pars.resize(0);
	pars.push_back(alpha1);
	pars.push_back(alpha2);
    pars.push_back(cur_F);
    if (!mySettings.get_infer_age()) {
        pars.push_back(start);
    } else {
        pars.push_back(age);
    }
	pars.push_back(new end_freq(curPath->get_traj(curPath->get_length()-1), random, curParamPath));
    std::vector<int> time_idx(0);
    for (int i = 0; i < sample_time_vec.size()-1; i++) {
        if (sample_time_vec[i]->get_oldest() < sample_time_vec[i]->get_youngest()) {
            if (!mySettings.get_infer_age()) {
                //std::cout << "ERROR: Cannot have uncertain times without inferring allele age. Will be fixed in the future" << std::endl;
                exit(1);
            }
            sample_time_vec[i]->set_path(curParamPath);
            pars.push_back(sample_time_vec[i]);
            time_idx.push_back(i);
        }
    }
	pars.push_back(curParamPath);

    
    //prepare output file
    //prepareOutput(mySettings.get_infer_age(), time_idx);
    
	//initialize the proposal ratios
	//probably move this somewhere else
	std::vector<double> propChance(0);
	propChance.push_back(mySettings.get_a1prop()); //update alpha1
	propChance.push_back(mySettings.get_a2prop()); //update alpha2
    
    ////////////////////LOOK HERE/////////////////////////
    propChance.push_back(mySettings.get_a2prop()); //update F TODO: THIS DOESN'T HAVE ITS OWN THING
	///////////////////LOOK HERE/////////////////////////
    
    propChance.push_back(mySettings.get_ageprop()); //update start/age
	propChance.push_back(mySettings.get_endprop()); //update end
    for (int i = 0; i < time_idx.size(); i++) {
        propChance.push_back(mySettings.get_timeprop()); //update times
    }
	propChance.push_back(mySettings.get_pathprop()); //update path

	//store as a cdf
	double sum = 0;
	for (int i = 0; i < propChance.size(); i++) {
		sum += propChance[i];
	}
	double cumsum = 0;
	for (int i = 0; i < propChance.size(); i++) {
		cumsum += propChance[i]/sum;
		propChance[i] = cumsum;
	}
    
    //determine if ascertained
    doAscertain = mySettings.get_ascertain();
    
    if (doAscertain) {
        double ssModern = sample_time_vec[sample_time_vec.size()-1]->get_ss();
        minCount = ceil(mySettings.get_min_freq()*ssModern);
        //std::cout << "Modeling ascertainment, assuming at least " << minCount << " copies of the derived allele at present and derived allele found in at least one ancient sample" << std::endl;
    }
    
    //clean up
    
    delete curWF;
    
	
	//compute starting lnL
	curlnL = compute_lnL_sample_only(curPath);
    
	//run mcmc
	for (gen = 0; gen < num_gen; gen++) {

		std::string state;
		double propRatio = 0;
		double priorRatio = 0;
		double u = random->uniformRv();
		//propose a parameter change
		for (curProp = 0; curProp < propChance.size(); curProp++) {
			if (u < propChance[curProp]) {
				break;
			}
		}
        
        //do the hard work
		pars[curProp]->increaseProp();
		propRatio = pars[curProp]->propose();
		priorRatio = pars[curProp]->prior();
        
        if (mySettings.get_fix_h() && curProp == 1) {
            pars[0]->setNew(pars[1]->get()*mySettings.get_h());
        }
		
        //TODO: DOES THIS DO ANYTHING??????
		//oldWF = curWF;
		//curWF = new wfMeasure(random,pars[0]->get());
		
        oldlnL = curlnL;
		curlnL = compute_lnL_sample_only(curPath);
		
		double LLRatio = curlnL-oldlnL;
        // if (curlnL != curlnL || oldlnL != oldlnL) {
        //     std::cout << "ERROR: likelihood is nan!" << std::endl;
        //     std::cout << "Generation = " << gen << std::endl;
        //     std::cout << "Proposal = " << curProp << std::endl;
        //     std::cout << "curlnL = " << curlnL << ", oldlnL = " << oldlnL << std::endl;
           // curPath->print();
            // for (int t = 0; t < sample_time_vec.size(); t++) {
            //     std::cout << sample_time_vec[t]->get() << std::endl;
            // }
          //  exit(1);
        //}
		if (curProp == 0 || curProp == 1) {
			//need to compute LL ratio due to the new alpha...
			cbpMeasure quickCBP(random);
			LLRatio += quickCBP.log_girsanov_wfwf_r(curPath, pars[0]->getOld(), pars[0]->get(), pars[1]->getOld(), pars[1]->get(), curPath->get_pop());
		}
		double mh = LLRatio+propRatio+priorRatio;
		u = random->uniformRv();
        
        // if (gen % printFreq == 0) {
        //     std::cout << gen << " " << curProp;
        //     std::cout << std::setprecision(10) <<  " " << oldlnL << " -> " << curlnL << " " << LLRatio << " " << propRatio << " " << priorRatio << " " << mh << " " << log(u) << " ";
        // }
        
		if (log(u) < mh) {
			//accept
			if (curProp < pars.size()-1) {
				pars[curProp]->increaseAccept();
			}
			curPath->set_update_begin(0);
			curPath->set_old_index(-1);
			//delete oldWF;
			state = "Accept";
		} else {
			//reject
			if (curProp < pars.size()) {
				pars[curProp]->reset();
			}
            
            if (mySettings.get_fix_h() && curProp == 1) {
                pars[0]->reset();
            }
			
			//delete curWF;
			//curWF = oldWF;
			curlnL = oldlnL;
			state = "Reject";
		}
	
		
        // if (gen % printFreq == 0) {
        //     std::cout << state << std::endl;
        // }

        
        for (int i = 0; i < sample_time_vec.size(); i++) {
            double curTime = sample_time_vec[i]->get();
            int curIdx = sample_time_vec[i]->get_idx();
            if (curIdx != -1) {
                double curTimePath = curPath->get_time(curIdx);
                if (curTime != curTimePath && curIdx != -1) {
                    // std::cout << "ERROR: sample time index for time " << i << " is lost!" << std::endl;
                    // std::cout << "curTime = " << curTime << std::endl;
                    // std::cout << "curIdx = " << curIdx << std::endl;
                    // std::cout << "curTimePath = " << curTimePath << std::endl;
                    exit(1);
                }
            }
        }
		
		int tuningFreq = num_gen/1000;
		if (tuningFreq < 100) {
			tuningFreq = 100;
		}
		if (tuningFreq > 1000) {
			tuningFreq = 1000;
		}
		if (gen % tuningFreq == 0) {
			for (int i = 0; i < pars.size()-1; i++) {
				pars[i]->updateTuning();
			}
		}
				
        
		if (gen % sampleFreq == 0) {
            printState();
            alpha_1_vector.push_back(pars[0]->get());
            alpha_2_vector.push_back(pars[1]->get());
		}

	}


    
    //drop first N alements from store vectors
    int N = 500;
    alpha_1_vector.erase(alpha_1_vector.begin(), alpha_1_vector.begin() + N);
    alpha_2_vector.erase(alpha_2_vector.begin(), alpha_2_vector.begin() + N);

    double sum_alpha_1 = std::accumulate(alpha_1_vector.begin(), alpha_1_vector.end(), 0.0);
    double mean_alpha_1 = sum_alpha_1 / alpha_1_vector.size();
    
    double sum_alpha_2 = std::accumulate(alpha_2_vector.begin(), alpha_2_vector.end(), 0.0);
    double mean_alpha_2 = sum_alpha_2 / alpha_2_vector.size();

    double sq_sum_alpha_1 = std::inner_product(alpha_1_vector.begin(), alpha_1_vector.end(), alpha_1_vector.begin(), 0.0);
    double stdev_alpha_1 = std::sqrt(sq_sum_alpha_1 / alpha_1_vector.size() - mean_alpha_1 * mean_alpha_1);

    double sq_sum_alpha_2 = std::inner_product(alpha_2_vector.begin(), alpha_2_vector.end(), alpha_2_vector.begin(), 0.0);
    double stdev_alpha_2 = std::sqrt(sq_sum_alpha_2 / alpha_2_vector.size() - mean_alpha_2 * mean_alpha_2);

    // std::cout << mean_alpha_1 << "," << stdev_alpha_1 << "," << mean_alpha_2 << "," << stdev_alpha_2 << std::endl;


    paramFile.open("results.csv", std::fstream::app);
    paramFile << mySettings.get_baseName() << "," <<mean_alpha_1 << "," << stdev_alpha_1 << "," << mean_alpha_2 << "," << stdev_alpha_2 << std::endl;
    paramFile.close();


    //paramFile << mean_alpha_1 << "," << stdev_alpha_1 << "," << mean_alpha_2 << "," << stdev_alpha_2 << std::endl;
    //paramFile.close();
    

//    paramFile.close();

    // std::cout << "\nOutput of alpha_1: ";
    // for (auto i = alpha_1_vector.cbegin(); i != alpha_1_vector.cend(); ++i)
    //     std::cout << *i << " ";
    // std::cout << "\nOutput of alpha_2: ";
    // for (auto i = alpha_2_vector.cbegin(); i != alpha_2_vector.cend(); ++i)
    //     std::cout << *i << " ";
    // //trajFile.close();
    //timeFile.close();
   

}




//for now, this computes the lnL of the WHOLE PATH (wrt Wiener measure) and SAMPLES
//could be optimized to only care about updated portions of path?
double mcmc::compute_lnL(wfSamplePath* p, measure* m, wienerMeasure* wm) {
	//compute dP/dW
	double gir = wm->log_girsanov(p, m, 0, PI);
	//compute sampling probs
	double sample_prob = 0;
	for (int i = 0; i < p->get_num_samples(); i++) {
		sample_prob += p->sampleProb(i);
	}
	
	if (gir != gir) {
		//std::cout << "Likelihood is nan at generation " << gen << ". Proposal " << curProp << std::endl;
		//p->print_traj(std::cout);
		//p->print_time(std::cout);
		exit(1);
	}
	return gir + sample_prob;
}

double mcmc::compute_lnL_sample_only(wfSamplePath* p) {
	double sample_prob = 0;
	for (int i = 0; i < p->get_num_samples(); i++) {
		sample_prob += p->sampleProb(i);
	}
    
    if (sample_prob == -INFINITY) {
        return -INFINITY;
    }
    
    if (doAscertain) {
        sample_prob -= ascertain(p);
    }
	
	return sample_prob;
}

double mcmc::ascertain(wfSamplePath* p) {
    double pA = 0;
    pA += p->ascertainModern(minCount);
    pA += p->ascertainAncient();
    return pA;
}

void mcmc::prepareOutput(bool infer_age, std::vector<int> time_idx) {
    //paramFile << "alpha1_mean,alpha1_std, alpha2_mean, alpha2_std";
    /*if (infer_age) {
        paramFile << "\tage";
    } else {
        paramFile << "\tstart_freq";
    }
    paramFile << "\tend_freq";
    for (int i = 0; i < time_idx.size(); i++) {
        paramFile << "\tsample_time_" << time_idx[i];
    }
    paramFile << "\tfirst_nonzero";
    */
    //paramFile << std::endl;
}

void mcmc::printState() {
    cbpMeasure testCBP(random);
    
    
    //double pathlnL = testCBP.log_girsanov_wf_r(curPath, pars[0]->get(), pars[1]->get(), curPath->get_pop(), 0);
    //paramFile << gen << "\t" << curlnL << "\t" << pathlnL;
    //paramFile << pars[0]->get() << "," << pars[1]->get();
    
    // alpha_1_vector.push_back(pars[0]->get());
    // alpha_2_vector.push_back(pars[1]->get());

    //paramFile << "\t" << pars[1]->get();
    //for (int i = 0; i < pars.size()-1; i++) {
    //    paramFile << "\t" << pars[i]->get();
    //}
    //paramFile << "\t" << curPath->get_firstNonzero();
    //paramFile << std::endl;
    //trajFile << gen << " ";
    //curPath->print_traj(trajFile << std::setprecision(20));
    //timeFile << gen << " ";
    //curPath->print_time(timeFile << std::setprecision(20));
}

