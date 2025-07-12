#include "GlobalHelper.h"

long ConcatenateHOGSIntoOGS(std::vector<CFastaFile*>* pvecFastaFileOrthogroups, std::vector<CFastaFile*>* pvecFastaFileHOGConcatenated, std::vector<CTable*>* pvecOrthoGroups)
{
	/*
	The goal of this program is to concatenate all HOGS into the same OGS.
	1) Sort the pvecFastaFile Orthogroups Alphabetically.
	2) Go over every row in the pvecOrthogroups (per .tsv file) and then per row in the tsv file (no need ot skip the first row in here since headers are stored separately)
	3) If Old OrthoGroup Name is the same the HOG (Fasta File) have to be found. The _ have to be replaced.
	4) Find Fasta File
	5) Copy all fasta blocks into the new fasta file
	6) Continue till old OG does not Match new OG, push back Fasta file and create new fasta file.
	7) Continue till nothing is left
	8) Push back the last fasta file
	
	*/



	long lReturn = ERR_NOERROR;

	//STEP ONE
	lReturn = SortFastaFilesAlphabeticallyFileName(pvecFastaFileOrthogroups);
	if (lReturn != ERR_NOERROR)
		return lReturn;

	//STEP TWO
	size_t sizeOrthoGroupTables = pvecOrthoGroups->size();
	size_t sizeTableRows = 0;
	size_t sizePosOfCharacterToBeReplaced = 0;
	size_t sizeFastaBlocks = 0;

	std::string strFastaFileOld;
	std::string strFastaFileNew;

	CTable* pTable = nullptr;
	CFastaFile* pFastaFile = nullptr;
	CFastaFile* pFastaFileToSearch = nullptr;
	CFastaBlock* pFastaBlock = nullptr;

	std::string strFastaFileNameHOGOrthoGroup;

	char* szFileNameToSearch = new char[SIZE_BUFFER_MEDIUM];
	CSmartPtr<char> pAutoDelete = szFileNameToSearch;
	memset(szFileNameToSearch, '\0', SIZE_BUFFER_MEDIUM);

	//strFastaFileOld = pvecOrthoGroups->


	for (size_t idx = 0; idx < sizeOrthoGroupTables; idx++) //For every .tsv file
	{
		pTable = pvecOrthoGroups->at(idx);
		sizeTableRows = pTable->GetAmountOfTableRows();

		//Get the old name as a starting point and create a new Fasta file object and set the Delete Rows on false, since it's stored in the source.
		strFastaFileOld = pTable->GetRow(0)->at(1);
		pFastaFile = new CFastaFile;	
		pFastaFile->SetDeleteRows(false);
		lReturn = pFastaFile->SetFastaFileName(strFastaFileOld);
		if (lReturn != ERR_NOERROR)
			return lReturn;

		for (size_t idx2 = 0; idx2 < sizeTableRows; idx2++) //For every row in A .tsv file
		{
			strFastaFileNew = pTable->GetRow(idx2)->at(1); //where the OG name is;

			//STEP THREE
			if (strcasecmp(strFastaFileNew.c_str(), strFastaFileOld.c_str()) != 0) //Not equal
			{
				//STEP SIX
				//PushBack the Fasta File
				pvecFastaFileHOGConcatenated->push_back(pFastaFile);
				pFastaFile = new CFastaFile;	
				pFastaFile->SetDeleteRows(false);

				strFastaFileOld = strFastaFileNew;
				lReturn = pFastaFile->SetFastaFileName(strFastaFileOld);
				if (lReturn != ERR_NOERROR)
					return lReturn;
			}

			//Find the Fasta File
			strFastaFileNameHOGOrthoGroup = pTable->GetRow(idx2)->at(0);
			sizePosOfCharacterToBeReplaced = strFastaFileNameHOGOrthoGroup.find('.', 0);
			strFastaFileNameHOGOrthoGroup.replace(sizePosOfCharacterToBeReplaced, 1, "_"); //Replacing N0.000000001 for N0_000000001

			memcpy(szFileNameToSearch, strFastaFileNameHOGOrthoGroup.c_str(), strFastaFileNameHOGOrthoGroup.length() + 1);

			//STEP FOUR
			lReturn = FindMatchingFastaFileFileName(pvecFastaFileOrthogroups, szFileNameToSearch, &pFastaFileToSearch);
			if (lReturn != ERR_NOERROR)
				return lReturn;

			//Reset the buffer
			memset(szFileNameToSearch, '\0', SIZE_BUFFER_MEDIUM);

			//STEP FIVE
			//We found the Fasta file now we have to copy all the fasta blocks into the OG fasta file.
			sizeFastaBlocks = pFastaFileToSearch->GetVectorSize();
			for (size_t idx3 = 0; idx3 < sizeFastaBlocks; idx3++)
			{
				pFastaBlock = pFastaFileToSearch->GetFastaBlock(idx3);
				pFastaFile->PushBackRowSafe(pFastaBlock);
			}
			

		}
		//STEP SEVEN AND EIGHT

		pvecFastaFileHOGConcatenated->push_back(pFastaFile);

	}



	return lReturn;

}