/*
 *  mcmc.h
 *  Selection_Recombination
 *
 *  Created by Joshua Schraiber on 5/2/13.
 *  Copyright 2013 UC Berkeley. All rights reserved.
 *
 */

#pragma once

#include <fstream>
#include <vector>

class wfSamplePath;
class measure;
class wienerMeasure;
class MbRandom;
class settings;
class param;
class sample_time;

class mcmc {

public:
	mcmc(settings& mySettings, MbRandom* r);
	
private:
	//variables to store
	double curlnL; 
	double oldlnL;
    std::vector<param*> pars;
    wfSamplePath* curPath;

	
	MbRandom* random;
	int num_gen;
	int printFreq;
	int sampleFreq;
	int minUpdate;
	void no_linked_sites(settings& mySettings);
	void linked_sites(settings& mySettings);
	
	// for debuging
	void no_linked_sites2(settings& mySettings);

	//for computing things
	double compute_lnL(wfSamplePath* p, measure* m, wienerMeasure* wm);
	
	double compute_lnL_sample_only(wfSamplePath* p);
    
    double ascertain(wfSamplePath* p);
	
	int gen;
	int curProp;
    
    //output files
    std::ofstream paramFile;
    //std::ofstream trajFile;
    //std::ofstream timeFile;

	//storing vectors
	//std::vector<double> alpha_1_vector;
    //std::vector<double> alpha_2_vector;
    
    //output functions
    void prepareOutput(bool infer_age, std::vector<int> time_idx);
    void printState();
	
    bool doAscertain;
    int minCount; 
};