#!/bin/bash

#Program Path
OSG_PATH=~/OSG_Debian.out #Edit to the path
#Orthofinder Output folder
ORTHOFINDER_OUTPUT= #You have to copy the N0.tsv to a new folder and use that folder as a path, since OSG use all .tsv files and we only need to use N0.tsv!!!! file can be found under <orthofinder_OutputFolder>/<Result...>/Phylogenetic_Hierarchical_Orthogroups/

#Original Fasta File folders
FASTA_FOLDER= #Your Orthofinder InputFolder
TAXONOMIC=~/TaxonomicGroup/Coleocheatephyceae_TaxonomicGroupFile_Ingroup_Set.txt  #Path to your taxonomic group files

#Minimum taxonomic group presents
MINIMUM_TAXONOMIC_GROUP=2 #Default is one

#Output folder
OUTPUT= #Output folder
SUMMARY_OUTPUT_FILE= #Output folder where you want to place it, I recommend to NOT use the OUTPUT directory, but like your work directory.


#Program format can be any order after program path
#[Program Path] -i [Orthofinder folder] -f [Fasta Folder] -o [Output Folder] -h [Taxonomic group file] -s [Number of minimum taxonomic groups -r
#-f <FastaFilesPath>\t\t Set the Path to the directory containing your fasta files: REQUIRED %s"
#-g <OrthoGroupFilesPath> \t\t Set the Path to the directory containing the Orthogroups in TSV format: REQUIRED%s"
#-r <OutputFolderPath>\t\t Set the Output Folder Path: REQUIRED %s"
#-t <TaxonomicGroupFile>\t\t Set the Taxonomic Group File, used to filter your result: NOT REQUIRED. If not Set all Orthogroups are parsed%s"
#-n <ThresholdNumber>\t\t Set the Threshold number of how many Taxonomic Groups need to be present: NOT REQUIRED. Not setting this value results in parsing all orthogroups!%s"
#-p \t\t Changes all fasta headers into the format needed for PhyloPyPruner: NOT REQUIRED. Not setting it will result in the same fasta headers as the fasta files uses.%s"
# -s <SummaryPath> \t\t Set the path to where the user want to write the Summary: NOT REQUIRED. Not setting it will result in no summary file.%s"
#-x        This ignores samples that are not within the taxonomic group file: NOT REQUIRED.
#-c        Combine all the HOGS into their OGs

#Standard use of OSG by also modifying the headers for the fasta output files from [Species]-[HeaderNumber] to [Species]@[HeaderNumber]
${OSG_PATH} -f ${FASTA_FOLDER} -g ${ORTHOFINDER_OUTPUT} -r ${OUTPUT} -t ${TAXONOMIC} -n ${MINIMUM_TAXONOMIC_GROUP} -s ${SUMMARY_OUTPUT_FILE} -p

#If you just want to create Orthogroup files out of all the HOGS. Keep in mind it will still say filtering in the HOGS to OGS as there are more HOGS than OGS ;)
#${OSG_PATH} -f ${FASTA_FOLDER} -g ${ORTHOFINDER_OUTPUT} -r ${OUTPUT} -s ${SUMMARY_OUTPUT_FILE} -p -c
