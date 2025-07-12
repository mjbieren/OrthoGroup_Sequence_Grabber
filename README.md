# OrthoGroup Sequence Grabber
This repository hosts the updated version of the Orthogroup Sequence Grabber, developed initially for the Klebsormidiophyceae phylogenomic study. As the tool has grown and gained more features over time, I've decided to maintain each tool for the PhyloRSeq++ pipeline in its own dedicated GitHub repository for clarity and modularity.

Orthogroup Sequence Grabber is very easy to use, you can either run it directly on the command line or by editing the script OSG.sh
This step is also very simple again. Just edit the [OSG.sh](https://github.com/mjbieren/Phylogenomics_klebsormidiophyceae/blob/main/Scripts/10_OrthogroupSequenceGrabber_OSG/OSG_Gandalf.sh) file and run it (Change lines 4 to 15).
This tool can run with just 1 CPU, and output files can not be bigger than 1 GB of RAM. It can run on any 64-bit machine on the front end and is super fast. 5% of the time is the calculations/parsing of the input files and 95% is writing them to the output folder. Which is heavily depending on the speed of your disks and/or your network speed.

If you require the size of the output files to change please contact me at maaikejacobine.bierenbroodspot@uni-goettingen.de



Basically, this tool interprets Orthofinder's tsv files under "Phylogenetic_Hierarchical_Orthogroups" and parses the Orthogroups in fasta objects, by obtaining the fasta blocks from the original fasta files (Orthofinder input folder). 
It is, however, recommended only to use the N0.tsv file (aka copy the N0.tsv file into its own directory and use that as an input.
It then filters this result based on the users' taxonomic group file and the threshold given by the user. This means that if you have a taxonomic group filter threshold of 2. You need at least 2 species of different taxonomic groups. Not two species of the same taxonomic group. See the folder [TaxonomicGroupFiles](https://github.com/mjbieren/OrthoGroup_Sequence_Grabber/upload/main/TaxonomicGroupFiles) for examples.
Basically, the Taxonomic Group file is formatted like this:
```
SpeciesName1(HeaderName),Speciesname2(HeaderName)
SpeciesName3(HeaderName),SpeciesName4(HeaderName)
```
Each line represents a taxonomic group, and species are separated by a ",".

## Visualisation
Based on the user-defined threshold, the program analyzes the various HOG TSV files. It filters out any orthogroups containing fewer than three sequences, as it's not possible to construct a phylogenetic tree with only one or two sequences.
Next, filtering is applied based on the taxonomic group threshold. In the example below, a threshold of 4 is used, meaning that an orthogroup must include sequences from at least four different taxonomic groups to be retained.

As illustrated in the image, an orthogroup with four sequences (indicated by green arrows) is excluded because those sequences do not represent four distinct taxonomic groups. Therefore, this orthogroup does not meet the threshold and is filtered out.
![alt text](https://github.com/mjbieren/OrthoGroup_Sequence_Grabber/blob/main/Sources/Images/OSG_Bad.PNG?raw=True "BAD_Filter")

In contrast, the image below shows an orthogroup with four sequences (indicated by green arrows), each representing a different taxonomic group. Since it meets the threshold, this orthogroup will be included in the creation of a FASTA files.
![alt text](https://github.com/mjbieren/OrthoGroup_Sequence_Grabber/blob/main/Sources/Images/OSG_Good.PNG?raw=True "GOOD_Filter")

The program then generates the corresponding FASTA output files, the number can become quite large depending on the filtering criteria used. This process is illustrated in the image below.
![alt text](https://github.com/mjbieren/OrthoGroup_Sequence_Grabber/blob/main/Sources/Images/OSG_Filtered.PNG?raw=True "Filtered")

Finally a summary file is created if the user wishes so.

### The Summary File
You have the option to create a summary file, which gives you an overview of what OSG did. Example output:

```
There were a total of 60931 OrthoGroups from the OrthoFinder Output, which was based on 126 taxa 
The Taxonomic Group file contained a total of 4 Taxonomic Groups
The User defined 2 as a Threshold, meaning 2/4 Taxonomic Groups had to be present for each OrthoGroup.
From the total of 60931 Orthogroups, 47522 were filtered out, resulting in 13409 Orthogroups, containing at least 2 Taxonomic Groups.

Each of these Orthogroups was written into a Fasta File.

```

## OSG (Orthogroup Sequence Grabber) Sources
This tool is created with the Boost library (v1.88). It is developed in Visual Studio 2019 with the GCC compiler (For remote Linux).  I've compiled two different (static) executables (they are portable!) under Debian 12 ([OSG_Debian.out]([https://github.com/mjbieren/Phylogenomics_klebsormidiophyceae/tree/main/Executables/OSG](https://github.com/mjbieren/OrthoGroup_Sequence_Grabber/tree/main/Executables))), and Rocky Linux 8, which is based on Linux Red Hat.

Either make your own executable with the corresponding source files or use one of the already existing executables.


### Command line options
Format to run Program:
```
[Program Path] -f [Fasta Folder] -g [Orthofinder folder] -r [Output Folder] -t [Taxonomic group file] -n [Threshold TaxonomicGroups] -p -s -x -c
```

Command line options:
```
-f <FastaFilesPath> 		Set the Path to the directory containing your fasta files: REQUIRED
-g <OrthoGroupFilesPath>	Set the Path to the directory containing the Orthogroups in TSV format: REQUIRED%
-r <OutputFolderPath>		Set the Output Folder Path: REQUIRED
-t <TaxonomicGroupFile>		Set the Taxonomic Group File, used to filter your result: NOT REQUIRED. 
				If not set, all Orthogroups are parsed
-n <ThresholdNumber>		Set the Threshold number of how many Taxonomic Groups need to be present: NOT REQUIRED.
				Not setting this value results in parsing all orthogroups!
-p				Changes all fasta headers into the format needed for PhyloPyPruner: NOT REQUIRED. 
				Not setting it will result in the same fasta headers as the fasta files use.
-s <SummaryPath>		Set the path to where the user wants to write the Summary: NOT REQUIRED. 
				Not setting it will result in no summary file: NOT REQUIRED.
-x				This ignores samples that are not within the taxonomic group file: NOT REQUIRED.
-c				Combine all the HOGS into their OGs
```
