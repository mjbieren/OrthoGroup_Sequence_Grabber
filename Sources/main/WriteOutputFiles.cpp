#include "GlobalHelper.h"


long WriteSummaryFile(size_t sizetotalOrthoGroups, size_t sizeFilteredOrthoGroups, char ** ppFileBuffer, size_t sizeBuffer, size_t sizeFastaFilesSource)
{
	long lReturn = ERR_NOERROR;

	std::string strSummaryPath;

	lReturn = glb.propertyBag.GetOutputSummary(&strSummaryPath);
	if (lReturn != ERR_NOERROR)
		return PROPERTYBAG_GET_SUMMARYPATH_OSG;

	std::string strTimeStamp = std::to_string(std::time(0)); //Get a timeStamp
	std::string strFullPath = strSummaryPath + strTimeStamp + "_Summary_OrthoGroupSequenceGrabber.txt";

	size_t sizeThreshold = 0;
	lReturn = glb.propertyBag.GetTaxonomicGroupThreshold(&sizeThreshold);
	if (lReturn != ERR_NOERROR)
		return PROPERTYBAG_TAXONOMICTHRESHOLD_OSG;

	
	size_t sizeTaxonomicGroups = 0;
	lReturn = glb.propertyBag.GetTaxonomicGroupVectorSize(&sizeTaxonomicGroups);
	if (lReturn != ERR_NOERROR)
		return PROPERTYBAG_GETTAXONOMICGROUPSIZE_VECTOR_OSG;

	FILE* hFileSummary = nullptr;

	printf_s("Create Summary OrthoGroup Sequence Grabber File: %s %s", strFullPath.c_str(), EOL);

	size_t sizeBufferLeft = sizeBuffer;

	char* pBufferPos = *ppFileBuffer;




	/*
	1) There were a total of xxx OrthoGroups from the OrthoFinder Output, which was based on xxx Strains EOL
	2) The Taxonomic Group file contained a total of xxxx Taxonomic Groups
	3) The User defined xxx as a Threshold, meaning xxxx/xxxx Taxonomic Groups had to be present for each orthogroup.
	4) From the total off xxxx Orthogorups, xxxx Where Filtered out resulting in xxxx Orthogroups, containing at least xxx Taxonomic Groups.
	5)
	6) Each of these Orthogroups was written into a Fasta File.
	
	*/

	sizeBufferLeft = sizeBufferLeft - (pBufferPos - *ppFileBuffer);
	pBufferPos += sprintf_s(pBufferPos, sizeBufferLeft, "There were a total of %zu OrthoGroups from the OrthoFinder Output, which was based on %zu taxa %s", sizetotalOrthoGroups, sizeFastaFilesSource,EOL); //LINE ONE
	sizeBufferLeft = sizeBufferLeft - (pBufferPos - *ppFileBuffer);
	pBufferPos += sprintf_s(pBufferPos, sizeBufferLeft, "The Taxonomic Group file contained a total of %zu Taxonomic Groups%s", sizeTaxonomicGroups, EOL); //LINE TWO
	sizeBufferLeft = sizeBufferLeft - (pBufferPos - *ppFileBuffer);
	pBufferPos += sprintf_s(pBufferPos, sizeBufferLeft, "The User defined %zu as a Threshold, meaning %zu/%zu Taxonomic Groups had to be present for each orthogroup.%s", sizeThreshold, sizeThreshold, sizeTaxonomicGroups, EOL); //LINE THREE
	sizeBufferLeft = sizeBufferLeft - (pBufferPos - *ppFileBuffer);
	pBufferPos += sprintf_s(pBufferPos, sizeBufferLeft, "From the total of %zu Orthogroups, %zu were filtered out, resulting in %zu Orthogroups, containing at least %zu Taxonomic Groups.%s", sizetotalOrthoGroups, sizetotalOrthoGroups-sizeFilteredOrthoGroups, sizeFilteredOrthoGroups, sizeThreshold,EOL); //LINE FOUR
	sizeBufferLeft = sizeBufferLeft - (pBufferPos - *ppFileBuffer);
	pBufferPos += sprintf_s(pBufferPos, sizeBufferLeft, "%s", EOL);//LINE FIVE
	sizeBufferLeft = sizeBufferLeft - (pBufferPos - *ppFileBuffer);
	pBufferPos += sprintf_s(pBufferPos, sizeBufferLeft, "Each of these Orthogroups was written into a Fasta File.%s", EOL);//LINE SIX

	errno_t errFopen_s =  fopen_s(&hFileSummary, strFullPath.c_str(), "wb");
	if (errFopen_s != ERR_NOERROR)
	{
		printf_s("Error RR_FOPEN_SUMMARY_FILE_WRITE: %s on fopen_s() %s, on line %i in file %s %s", strFullPath.c_str(), __LINE__, __FILE__,EOL);
		return WRITE_OUTPUT_FILE_SUMMARY_OSG;
	}
	else
	{
		fputs(*ppFileBuffer, hFileSummary);
	}
	fclose(hFileSummary);



	return lReturn;
}

long WriteFastaFile(CFastaFile* pFastaFile, std::string strDirPath, char ** ppFileBuffer, bool bPhyloPyPrunerFormat, size_t sizeBuffer)
{
	//This function is to write a Fasta file
	/*
	1) Get the Fasta File Name from the pFastaFile Object
	2) Determine if we have a phylopypruner format. If so the order of executing will be = >StrainName@HeaderNumber EOL SequenceEOL
	*/

	long lReturn = ERR_NOERROR;

	char* pFastaFileName = nullptr;
	lReturn = pFastaFile->GetFastaFileName(&pFastaFileName);
	if (lReturn != ERR_NOERROR)
		return lReturn;

	std::string strFullFilePath = strDirPath + pFastaFileName + ".fa";

	CFastaBlock* pCurrentFastaBlock = nullptr;
	size_t sizeFastaBlockVector = pFastaFile->GetVectorSize();

	char* pBufferPos = *ppFileBuffer;

	size_t sizeBufferLeft = sizeBuffer;

	//Fill The buffer
	if (bPhyloPyPrunerFormat == false)
	{
		for (size_t idx = 0; idx < sizeFastaBlockVector; idx++)
		{
			sizeBufferLeft = sizeBufferLeft - (pBufferPos - *ppFileBuffer);
			pCurrentFastaBlock = pFastaFile->GetFastaBlock(idx);
			pBufferPos += sprintf_s(pBufferPos, sizeBufferLeft, ">%s%s%s%s", pCurrentFastaBlock->GetFastaHeader(), EOL, pCurrentFastaBlock->GetFastaSequence(), EOL);

		}
	}
	else
	{
		for (size_t idx = 0; idx < sizeFastaBlockVector; idx++)
		{
			sizeBufferLeft = sizeBufferLeft - (pBufferPos - *ppFileBuffer);
			pCurrentFastaBlock = pFastaFile->GetFastaBlock(idx);
			//pBufferPos += sprintf_s(pBufferPos, sizeBufferLeft, ">%s%s%lu%s%s%s", pCurrentFastaBlock->GetFastaHeaderStrain(),"@",pCurrentFastaBlock->GetHeaderNumber() ,EOL, pCurrentFastaBlock->GetFastaSequence(), EOL);
			pBufferPos += sprintf_s(pBufferPos, sizeBufferLeft, ">%s%s%s%s%s%s", pCurrentFastaBlock->GetFastaHeaderStrain(),"@",pCurrentFastaBlock->GetFastaHeaderRest() ,EOL, pCurrentFastaBlock->GetFastaSequence(), EOL);

		}
	}

	//Remove last EOL
	pBufferPos--;
	*pBufferPos = '\0';

	FILE* hFileOutputFasta = nullptr;

	errno_t errFopen_s =  fopen_s(&hFileOutputFasta, strFullFilePath.c_str(), "wb");
		if (errFopen_s != ERR_NOERROR)
		{
			printf_s("Error in opening fasta file %s, on line %i in file %s %s", strFullFilePath.c_str(), __LINE__, __FILE__,EOL);
			return WRITE_OUTPUT_FILE_ERROR_FOPEN;
		}
		else
		{
			fputs(*ppFileBuffer, hFileOutputFasta);
		}
		fclose(hFileOutputFasta);

	return lReturn;
}

long WriteOutputFiles(std::vector<CFastaFile*>* pvecFastaFileOrthoGroupsFiltered, size_t sizeTotalOrthoGroups, size_t sizeFastaFilesSource)
{
	long lReturn = ERR_NOERROR;

	//This function writes all the fasta files with the Orthogroup names and a summary file
	//1) Check if the user want the PhylopyPruner Format or not
	//2) Loop over the vector Fasta file
	//3) Print out every 50 fasta files how for we are.
	//4) Write the Fasta File
	//5) Write the Summary File

	size_t sizeFilteredAmount = pvecFastaFileOrthoGroupsFiltered->size();

	printf_s("From the %zu total orthogroups, we have a total %zu Orthogroups after the taxonomic group filter %s", sizeTotalOrthoGroups, sizeFilteredAmount, EOL);

	
	std::string strFastaDirOutput;
	lReturn = glb.propertyBag.GetOutputFolderPath(&strFastaDirOutput);
	if (lReturn != ERR_NOERROR)
		return PROPERTYBAG_GETFASTADIR_OSG;

	//Set the File Buffer for all the files.
	char* pBuffer = new char[SIZE_BUFFER_ONE_GIG];
	CSmartPtr<char> pAutoDelete = pBuffer; //Create smart pointer so that we do not have to keep track of it.
	memset(pBuffer, '\0', SIZE_BUFFER_BIG); //Set all characters as zero terminated.


	//STEP ONE
	bool bPhyloPyPrunerFormat = false;
	lReturn = glb.propertyBag.GetPhyloPyPrunerFormat(&bPhyloPyPrunerFormat);
	if (lReturn != ERR_NOERROR)
		return PROPERTYBAG_PHYLOPYPRUNERFORMAT_OSG;


	CFastaFile* pFasta = nullptr;

	//STEP TWO
	for (size_t idx = 0; idx < sizeFilteredAmount; idx++)
	{
		pFasta = pvecFastaFileOrthoGroupsFiltered->at(idx);
		if (!pFasta)
			return WRITE_OUTPUT_ORTHOGROUP_FASTAOBJECT;

		//Reset the buffer
		memset(pBuffer, '\0', SIZE_BUFFER_BIG);

		//STEP THREE
		if (idx % 50 == 0) //We do not want to print out that we are writing a file for each file only every 50.
			printf_s("Write Orthogroup to fasta file format. File %zu out of %zu %s", idx+1, sizeFilteredAmount, EOL);

		//STEP FOUR
		lReturn = WriteFastaFile(pFasta, strFastaDirOutput, &pBuffer, bPhyloPyPrunerFormat, SIZE_BUFFER_ONE_GIG);
		if (lReturn != ERR_NOERROR)
			return lReturn;
	}

	printf_s("Done with writing all the Orthogroup fasta files %s", EOL);

	//STEP FIVE
	bool bSummaryFile = false;

	lReturn = glb.propertyBag.GetBoolSummary(&bSummaryFile);
	if (lReturn != ERR_NOERROR)
		return PROPERTYBAG_GET_BOOLSUMMARY_OSG;

	if (bSummaryFile == true)
	{
		printf_s("Time to Write the Summary File %s", EOL);
		//Reset the buffer
		memset(pBuffer, '\0', SIZE_BUFFER_BIG);

		lReturn = WriteSummaryFile(sizeTotalOrthoGroups, sizeFilteredAmount, &pBuffer, SIZE_BUFFER_BIG, sizeFastaFilesSource);
		if (lReturn != ERR_NOERROR)
			return lReturn;

		printf_s("Done with Writing the Summary File %s", EOL);


	}
	


	return lReturn;
}


