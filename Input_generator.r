setwd("C:/Users/ACER/Desktop/Undergraduate dissertation/v44.3_1240K_public")
getwd()

# GENERATING INPUTS FOR SCHRAIBER'S CODE

# Certainly, there are many ways in which this process could've been optimized, 
# but for 12 time periods it was not worth it to write custom functions for 
# each step. Instead, you can just change the population identifiers (in this 
# case "ib" for Iberia being the default one).


# 1. Extract allele count from plink frq files. 

ib500_frq = read.table("iberian_cline500.frq", header = TRUE)
ib500_frq = ib500_frq[ , c(1,2,5,6)]
ib500_frq = ib500_frq[complete.cases(ib500_frq), ]
Count = ib500_frq$MAF * ib500_frq$NCHROBS
Count = round(Count, digits = 0)
ib500_frq = cbind(ib500_frq, Count)
ib500_frq = ib500_frq[ , c(1,2,5,4)]

ib1000_frq = read.table("iberian_cline1000.frq", header = TRUE)
ib1000_frq = ib1000_frq[ , c(1,2,5,6)]
ib1000_frq = ib1000_frq[complete.cases(ib1000_frq), ]
Count = ib1000_frq$MAF * ib1000_frq$NCHROBS
Count = round(Count, digits = 0)
ib1000_frq = cbind(ib1000_frq, Count)
ib1000_frq = ib1000_frq[ , c(1,2,5,4)]

ib1500_frq = read.table("iberian_cline1500.frq", header = TRUE)
ib1500_frq = ib1500_frq[ , c(1,2,5,6)]
ib1500_frq = ib1500_frq[complete.cases(ib1500_frq), ]
Count = ib1500_frq$MAF * ib1500_frq$NCHROBS
Count = round(Count, digits = 0)
ib1500_frq = cbind(ib1500_frq, Count)
ib1500_frq = ib1500_frq[ , c(1,2,5,4)]

ib2000_frq = read.table("iberian_cline2000.frq", header = TRUE)
ib2000_frq = ib2000_frq[ , c(1,2,5,6)]
ib2000_frq = ib2000_frq[complete.cases(ib2000_frq), ]
Count = ib2000_frq$MAF * ib2000_frq$NCHROBS
Count = round(Count, digits = 0)
ib2000_frq = cbind(ib2000_frq, Count)
ib2000_frq = ib2000_frq[ , c(1,2,5,4)]

ib2500_frq = read.table("iberian_cline2500.frq", header = TRUE)
ib2500_frq = ib2500_frq[ , c(1,2,5,6)]
ib2500_frq = ib2500_frq[complete.cases(ib2500_frq), ]
Count = ib2500_frq$MAF * ib2500_frq$NCHROBS
Count = round(Count, digits = 0)
ib2500_frq = cbind(ib2500_frq, Count)
ib2500_frq = ib2500_frq[ , c(1,2,5,4)]

ib3000_frq = read.table("iberian_cline3000.frq", header = TRUE)
ib3000_frq = ib3000_frq[ , c(1,2,5,6)]
ib3000_frq = ib3000_frq[complete.cases(ib3000_frq), ]
Count = ib3000_frq$MAF * ib3000_frq$NCHROBS
Count = round(Count, digits = 0)
ib3000_frq = cbind(ib3000_frq, Count)
ib3000_frq = ib3000_frq[ , c(1,2,5,4)]

ib3500_frq = read.table("iberian_cline3500.frq", header = TRUE)
ib3500_frq = ib3500_frq[ , c(1,2,5,6)]
ib3500_frq = ib3500_frq[complete.cases(ib3500_frq), ]
Count = ib3500_frq$MAF * ib3500_frq$NCHROBS
Count = round(Count, digits = 0)
ib3500_frq = cbind(ib3500_frq, Count)
ib3500_frq = ib3500_frq[ , c(1,2,5,4)]

ib4000_frq = read.table("iberian_cline4000.frq", header = TRUE)
ib4000_frq = ib4000_frq[ , c(1,2,5,6)]
ib4000_frq = ib4000_frq[complete.cases(ib4000_frq), ]
Count = ib4000_frq$MAF * ib4000_frq$NCHROBS
Count = round(Count, digits = 0)
ib4000_frq = cbind(ib4000_frq, Count)
ib4000_frq = ib4000_frq[ , c(1,2,5,4)]

ib4500_frq = read.table("iberian_cline4500.frq", header = TRUE)
ib4500_frq = ib4500_frq[ , c(1,2,5,6)]
ib4500_frq = ib4500_frq[complete.cases(ib4500_frq), ]
Count = ib4500_frq$MAF * ib4500_frq$NCHROBS
Count = round(Count, digits = 0)
ib4500_frq = cbind(ib4500_frq, Count)
ib4500_frq = ib4500_frq[ , c(1,2,5,4)]

ib5000_frq = read.table("iberian_cline5000.frq", header = TRUE)
ib5000_frq = ib5000_frq[ , c(1,2,5,6)]
ib5000_frq = ib5000_frq[complete.cases(ib5000_frq), ]
Count = ib5000_frq$MAF * ib5000_frq$NCHROBS
Count = round(Count, digits = 0)
ib5000_frq = cbind(ib5000_frq, Count)
ib5000_frq = ib5000_frq[ , c(1,2,5,4)]

ib5500_frq = read.table("iberian_cline5500.frq", header = TRUE)
ib5500_frq = ib5500_frq[ , c(1,2,5,6)]
ib5500_frq = ib5500_frq[complete.cases(ib5500_frq), ]
Count = ib5500_frq$MAF * ib5500_frq$NCHROBS
Count = round(Count, digits = 0)
ib5500_frq = cbind(ib5500_frq, Count)
ib5500_frq = ib5500_frq[ , c(1,2,5,4)]

ib6000_frq = read.table("iberian_cline6000.frq", header = TRUE)
ib6000_frq = ib6000_frq[ , c(1,2,5,6)]
ib6000_frq = ib6000_frq[complete.cases(ib6000_frq), ]
Count = ib6000_frq$MAF * ib6000_frq$NCHROBS
Count = round(Count, digits = 0)
ib6000_frq = cbind(ib6000_frq, Count)
ib6000_frq = ib6000_frq[ , c(1,2,5,4)]

# 2. Standardize the sample - assure that every set contains the same SNPs.

ib500_frq = ib500_frq[ib500_frq$SNP %in% ib1000_frq$SNP,]
ib500_frq = ib500_frq[ib500_frq$SNP %in% ib1500_frq$SNP,]
ib500_frq = ib500_frq[ib500_frq$SNP %in% ib2000_frq$SNP,]
ib500_frq = ib500_frq[ib500_frq$SNP %in% ib2500_frq$SNP,]
ib500_frq = ib500_frq[ib500_frq$SNP %in% ib3000_frq$SNP,]
ib500_frq = ib500_frq[ib500_frq$SNP %in% ib3500_frq$SNP,]
ib500_frq = ib500_frq[ib500_frq$SNP %in% ib4000_frq$SNP,]
ib500_frq = ib500_frq[ib500_frq$SNP %in% ib4500_frq$SNP,]
ib500_frq = ib500_frq[ib500_frq$SNP %in% ib5000_frq$SNP,]
ib500_frq = ib500_frq[ib500_frq$SNP %in% ib5500_frq$SNP,]
ib500_frq = ib500_frq[ib500_frq$SNP %in% ib6000_frq$SNP,]

ib1000_frq = ib1000_frq[ib1000_frq$SNP %in% ib500_frq$SNP,]
ib1000_frq = ib1000_frq[ib1000_frq$SNP %in% ib1500_frq$SNP,]
ib1000_frq = ib1000_frq[ib1000_frq$SNP %in% ib2000_frq$SNP,]
ib1000_frq = ib1000_frq[ib1000_frq$SNP %in% ib2500_frq$SNP,]
ib1000_frq = ib1000_frq[ib1000_frq$SNP %in% ib3000_frq$SNP,]
ib1000_frq = ib1000_frq[ib1000_frq$SNP %in% ib3500_frq$SNP,]
ib1000_frq = ib1000_frq[ib1000_frq$SNP %in% ib4000_frq$SNP,]
ib1000_frq = ib1000_frq[ib1000_frq$SNP %in% ib4500_frq$SNP,]
ib1000_frq = ib1000_frq[ib1000_frq$SNP %in% ib5000_frq$SNP,]
ib1000_frq = ib1000_frq[ib1000_frq$SNP %in% ib5500_frq$SNP,]
ib1000_frq = ib1000_frq[ib1000_frq$SNP %in% ib6000_frq$SNP,]

ib1500_frq = ib1500_frq[ib1500_frq$SNP %in% ib1000_frq$SNP,]
ib1500_frq = ib1500_frq[ib1500_frq$SNP %in% ib500_frq$SNP,]
ib1500_frq = ib1500_frq[ib1500_frq$SNP %in% ib2000_frq$SNP,]
ib1500_frq = ib1500_frq[ib1500_frq$SNP %in% ib2500_frq$SNP,]
ib1500_frq = ib1500_frq[ib1500_frq$SNP %in% ib3000_frq$SNP,]
ib1500_frq = ib1500_frq[ib1500_frq$SNP %in% ib3500_frq$SNP,]
ib1500_frq = ib1500_frq[ib1500_frq$SNP %in% ib4000_frq$SNP,]
ib1500_frq = ib1500_frq[ib1500_frq$SNP %in% ib4500_frq$SNP,]
ib1500_frq = ib1500_frq[ib1500_frq$SNP %in% ib5000_frq$SNP,]
ib1500_frq = ib1500_frq[ib1500_frq$SNP %in% ib5500_frq$SNP,]
ib1500_frq = ib1500_frq[ib1500_frq$SNP %in% ib6000_frq$SNP,]

ib2000_frq = ib2000_frq[ib2000_frq$SNP %in% ib500_frq$SNP,]
ib2000_frq = ib2000_frq[ib2000_frq$SNP %in% ib1500_frq$SNP,]
ib2000_frq = ib2000_frq[ib2000_frq$SNP %in% ib1000_frq$SNP,]
ib2000_frq = ib2000_frq[ib2000_frq$SNP %in% ib2500_frq$SNP,]
ib2000_frq = ib2000_frq[ib2000_frq$SNP %in% ib3000_frq$SNP,]
ib2000_frq = ib2000_frq[ib2000_frq$SNP %in% ib3500_frq$SNP,]
ib2000_frq = ib2000_frq[ib2000_frq$SNP %in% ib4000_frq$SNP,]
ib2000_frq = ib2000_frq[ib2000_frq$SNP %in% ib4500_frq$SNP,]
ib2000_frq = ib2000_frq[ib2000_frq$SNP %in% ib5000_frq$SNP,]
ib2000_frq = ib2000_frq[ib2000_frq$SNP %in% ib5500_frq$SNP,]
ib2000_frq = ib2000_frq[ib2000_frq$SNP %in% ib6000_frq$SNP,]

ib2500_frq = ib2500_frq[ib2500_frq$SNP %in% ib1000_frq$SNP,]
ib2500_frq = ib2500_frq[ib2500_frq$SNP %in% ib500_frq$SNP,]
ib2500_frq = ib2500_frq[ib2500_frq$SNP %in% ib2000_frq$SNP,]
ib2500_frq = ib2500_frq[ib2500_frq$SNP %in% ib1500_frq$SNP,]
ib2500_frq = ib2500_frq[ib2500_frq$SNP %in% ib3000_frq$SNP,]
ib2500_frq = ib2500_frq[ib2500_frq$SNP %in% ib3500_frq$SNP,]
ib2500_frq = ib2500_frq[ib2500_frq$SNP %in% ib4000_frq$SNP,]
ib2500_frq = ib2500_frq[ib2500_frq$SNP %in% ib4500_frq$SNP,]
ib2500_frq = ib2500_frq[ib2500_frq$SNP %in% ib5000_frq$SNP,]
ib2500_frq = ib2500_frq[ib2500_frq$SNP %in% ib5500_frq$SNP,]
ib2500_frq = ib2500_frq[ib2500_frq$SNP %in% ib6000_frq$SNP,]

ib3000_frq = ib3000_frq[ib3000_frq$SNP %in% ib500_frq$SNP,]
ib3000_frq = ib3000_frq[ib3000_frq$SNP %in% ib1500_frq$SNP,]
ib3000_frq = ib3000_frq[ib3000_frq$SNP %in% ib1000_frq$SNP,]
ib3000_frq = ib3000_frq[ib3000_frq$SNP %in% ib2500_frq$SNP,]
ib3000_frq = ib3000_frq[ib3000_frq$SNP %in% ib2000_frq$SNP,]
ib3000_frq = ib3000_frq[ib3000_frq$SNP %in% ib3500_frq$SNP,]
ib3000_frq = ib3000_frq[ib3000_frq$SNP %in% ib4000_frq$SNP,]
ib3000_frq = ib3000_frq[ib3000_frq$SNP %in% ib4500_frq$SNP,]
ib3000_frq = ib3000_frq[ib3000_frq$SNP %in% ib5000_frq$SNP,]
ib3000_frq = ib3000_frq[ib3000_frq$SNP %in% ib5500_frq$SNP,]
ib3000_frq = ib3000_frq[ib3000_frq$SNP %in% ib6000_frq$SNP,]

ib3500_frq = ib3500_frq[ib3500_frq$SNP %in% ib1000_frq$SNP,]
ib3500_frq = ib3500_frq[ib3500_frq$SNP %in% ib500_frq$SNP,]
ib3500_frq = ib3500_frq[ib3500_frq$SNP %in% ib2000_frq$SNP,]
ib3500_frq = ib3500_frq[ib3500_frq$SNP %in% ib1500_frq$SNP,]
ib3500_frq = ib3500_frq[ib3500_frq$SNP %in% ib3000_frq$SNP,]
ib3500_frq = ib3500_frq[ib3500_frq$SNP %in% ib2500_frq$SNP,]
ib3500_frq = ib3500_frq[ib3500_frq$SNP %in% ib4000_frq$SNP,]
ib3500_frq = ib3500_frq[ib3500_frq$SNP %in% ib4500_frq$SNP,]
ib3500_frq = ib3500_frq[ib3500_frq$SNP %in% ib5000_frq$SNP,]
ib3500_frq = ib3500_frq[ib3500_frq$SNP %in% ib5500_frq$SNP,]
ib3500_frq = ib3500_frq[ib3500_frq$SNP %in% ib6000_frq$SNP,]

ib4000_frq = ib4000_frq[ib4000_frq$SNP %in% ib500_frq$SNP,]
ib4000_frq = ib4000_frq[ib4000_frq$SNP %in% ib1500_frq$SNP,]
ib4000_frq = ib4000_frq[ib4000_frq$SNP %in% ib1000_frq$SNP,]
ib4000_frq = ib4000_frq[ib4000_frq$SNP %in% ib2500_frq$SNP,]
ib4000_frq = ib4000_frq[ib4000_frq$SNP %in% ib2000_frq$SNP,]
ib4000_frq = ib4000_frq[ib4000_frq$SNP %in% ib3500_frq$SNP,]
ib4000_frq = ib4000_frq[ib4000_frq$SNP %in% ib3000_frq$SNP,]
ib4000_frq = ib4000_frq[ib4000_frq$SNP %in% ib4500_frq$SNP,]
ib4000_frq = ib4000_frq[ib4000_frq$SNP %in% ib5000_frq$SNP,]
ib4000_frq = ib4000_frq[ib4000_frq$SNP %in% ib5500_frq$SNP,]
ib4000_frq = ib4000_frq[ib4000_frq$SNP %in% ib6000_frq$SNP,]

ib4500_frq = ib4500_frq[ib4500_frq$SNP %in% ib1000_frq$SNP,]
ib4500_frq = ib4500_frq[ib4500_frq$SNP %in% ib500_frq$SNP,]
ib4500_frq = ib4500_frq[ib4500_frq$SNP %in% ib2000_frq$SNP,]
ib4500_frq = ib4500_frq[ib4500_frq$SNP %in% ib1500_frq$SNP,]
ib4500_frq = ib4500_frq[ib4500_frq$SNP %in% ib3000_frq$SNP,]
ib4500_frq = ib4500_frq[ib4500_frq$SNP %in% ib2500_frq$SNP,]
ib4500_frq = ib4500_frq[ib4500_frq$SNP %in% ib4000_frq$SNP,]
ib4500_frq = ib4500_frq[ib4500_frq$SNP %in% ib3500_frq$SNP,]
ib4500_frq = ib4500_frq[ib4500_frq$SNP %in% ib5000_frq$SNP,]
ib4500_frq = ib4500_frq[ib4500_frq$SNP %in% ib5500_frq$SNP,]
ib4500_frq = ib4500_frq[ib4500_frq$SNP %in% ib6000_frq$SNP,]

ib5000_frq = ib5000_frq[ib5000_frq$SNP %in% ib500_frq$SNP,]
ib5000_frq = ib5000_frq[ib5000_frq$SNP %in% ib1500_frq$SNP,]
ib5000_frq = ib5000_frq[ib5000_frq$SNP %in% ib1000_frq$SNP,]
ib5000_frq = ib5000_frq[ib5000_frq$SNP %in% ib2500_frq$SNP,]
ib5000_frq = ib5000_frq[ib5000_frq$SNP %in% ib2000_frq$SNP,]
ib5000_frq = ib5000_frq[ib5000_frq$SNP %in% ib3500_frq$SNP,]
ib5000_frq = ib5000_frq[ib5000_frq$SNP %in% ib3000_frq$SNP,]
ib5000_frq = ib5000_frq[ib5000_frq$SNP %in% ib4500_frq$SNP,]
ib5000_frq = ib5000_frq[ib5000_frq$SNP %in% ib4000_frq$SNP,]
ib5000_frq = ib5000_frq[ib5000_frq$SNP %in% ib5500_frq$SNP,]
ib5000_frq = ib5000_frq[ib5000_frq$SNP %in% ib6000_frq$SNP,]

ib5500_frq = ib5500_frq[ib5500_frq$SNP %in% ib1000_frq$SNP,]
ib5500_frq = ib5500_frq[ib5500_frq$SNP %in% ib500_frq$SNP,]
ib5500_frq = ib5500_frq[ib5500_frq$SNP %in% ib2000_frq$SNP,]
ib5500_frq = ib5500_frq[ib5500_frq$SNP %in% ib1500_frq$SNP,]
ib5500_frq = ib5500_frq[ib5500_frq$SNP %in% ib3000_frq$SNP,]
ib5500_frq = ib5500_frq[ib5500_frq$SNP %in% ib2500_frq$SNP,]
ib5500_frq = ib5500_frq[ib5500_frq$SNP %in% ib4000_frq$SNP,]
ib5500_frq = ib5500_frq[ib5500_frq$SNP %in% ib3500_frq$SNP,]
ib5500_frq = ib5500_frq[ib5500_frq$SNP %in% ib5000_frq$SNP,]
ib5500_frq = ib5500_frq[ib5500_frq$SNP %in% ib4500_frq$SNP,]
ib5500_frq = ib5500_frq[ib5500_frq$SNP %in% ib6000_frq$SNP,]

ib6000_frq = ib6000_frq[ib6000_frq$SNP %in% ib500_frq$SNP,]
ib6000_frq = ib6000_frq[ib6000_frq$SNP %in% ib1500_frq$SNP,]
ib6000_frq = ib6000_frq[ib6000_frq$SNP %in% ib1000_frq$SNP,]
ib6000_frq = ib6000_frq[ib6000_frq$SNP %in% ib2500_frq$SNP,]
ib6000_frq = ib6000_frq[ib6000_frq$SNP %in% ib2000_frq$SNP,]
ib6000_frq = ib6000_frq[ib6000_frq$SNP %in% ib3500_frq$SNP,]
ib6000_frq = ib6000_frq[ib6000_frq$SNP %in% ib3000_frq$SNP,]
ib6000_frq = ib6000_frq[ib6000_frq$SNP %in% ib4500_frq$SNP,]
ib6000_frq = ib6000_frq[ib6000_frq$SNP %in% ib4000_frq$SNP,]
ib6000_frq = ib6000_frq[ib6000_frq$SNP %in% ib5500_frq$SNP,]
ib6000_frq = ib6000_frq[ib6000_frq$SNP %in% ib5000_frq$SNP,]

# 3. Write down the start and end points for each time period (based on meta 
# data provided by AADR for the analysed population).

starting_times = c(-5500, -4906, -4240, -3935, -3461, -3013, 
                   -2471, -2045, -1550,  -971,  -492,  -400)

ending_times = c(-6123, -5535, -5051, -4507, -4001, -3517, 
                 -3044, -2527, -1947, -1504, -1094,  -400)


# 4. Create a function to generate the outputs. Input the number of row from
# the data sets generated above.

sr_input = function(i) {
  result = rbind(ib6000_frq[i,], ib5500_frq[i,], ib5000_frq[i,], ib4500_frq[i,],
                 ib4000_frq[i,], ib3500_frq[i,], ib3000_frq[i,], ib2500_frq[i,], 
                 ib2000_frq[i,], ib1500_frq[i,], ib1000_frq[i,], ib500_frq[i,])
  df = data.frame(result)
  df = df[, c(3,4)]
  df = cbind(df, ending_times, starting_times)
  write.table(df, ib500_frq[i,2], col.names = FALSE, row.names = FALSE, sep="\t")
  return(df)
}

# 5. Change the directory to the desired location for input files for 
# Schraiber's algorithm.

setwd("C:/Users/ACER/Desktop/Inputs") 
getwd()

# 6. Loop the sr_input function over desired number of rows. 

for (i in 1:20) {
  sr_input(i)
}








 