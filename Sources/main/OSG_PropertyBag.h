#pragma once

#include "stdafx.h"
#include "Management.h"

class COSGPropertyBag : CPropertyBag
{
protected:
	char m_szGetOrthoGroupSequenceGrabberErrMessage[255];
public:
	COSGPropertyBag() {};
	~COSGPropertyBag() {};
	const char* GetLastOrthoGroupSequenceGrabberErrorMessage() { return m_szGetOrthoGroupSequenceGrabberErrMessage; }

/*
Fasta File Directory
OrthoGroup Dir
Output Directory
Taxonomic Group File
Taxonomoic Group threshold
Phylopypruner Format
*/
	long SetTaxonomicGroupVectorSize(size_t sizeTaxonomicGroupsize)
	{
		return SetValueSizeT("TaxonomicGroup", "VectorSize", sizeTaxonomicGroupsize);
	}

	long GetTaxonomicGroupVectorSize(size_t* psizeTaxonomicGroup)
	{
		long lReturn = ERR_NOERROR;
		lReturn = GetValueSizeT("TaxonomicGroup", "VectorSize", psizeTaxonomicGroup, 1);
		if (lReturn == PROP_ERR_SECTION_NOT_FOUND_DEFAULT_USED || lReturn == PROP_ERR_KEY_NOT_FOUND_DEFAULT_USED)
		{
			printf_s("%s %s","No Taxonomic group filtering file : Default 1 used",EOL);
			return ERR_NOERROR;
		}
		return lReturn;
	}


	long SetFastaDirPath(const char* szFastaDirPath)
	{
		std::string strFastaPath = szFastaDirPath;
		AppendSlash(&strFastaPath); //This is to make sure the path ends with a /
		return SetValueString("Paths", "FastaFiles", strFastaPath.c_str());
	}

	long GetFastaDirPath(std::string* pstrFastaQueryPath)
	{
		return GetValueString("Paths", "FastaFiles", pstrFastaQueryPath);
	}

	long SetOrthoGroupDirPath(const char* szOGDirPath)
	{
		std::string strOGPath = szOGDirPath;
		AppendSlash(&strOGPath);
		return SetValueString("Paths", "OrthoGroups", strOGPath.c_str());
	}

	long GetOrthoGroupDirPath(std::string* pstrOrthoGroupsPath)
	{
		return GetValueString("Paths", "OrthoGroups", pstrOrthoGroupsPath);
	}

	long SetOutputFolderPath(const char* szOutputPath)
	{
		std::string strOutputPath = szOutputPath;
		AppendSlash(&strOutputPath);
		return SetValueString("Paths", "Output", strOutputPath.c_str());
	}

	long GetOutputFolderPath(std::string* pstrOutputPath)
	{
		return GetValueString("Paths", "Output", pstrOutputPath);
	}

	long SetOutputSummaryPath(const char* szOutputSummary)
	{
		std::string strOutputSummary = szOutputSummary;
		AppendSlash(&strOutputSummary);
		return SetValueString("Paths", "Summary", strOutputSummary.c_str());
	}

	long GetOutputSummary(std::string* pstrOutputSummary)
	{
		return GetValueString("Paths", "Summary", pstrOutputSummary);
	}

	long SetBoolSummary(bool bSetSummary = true)
	{
		return SetValueBool("Bool", "Summary", bSetSummary);
	}

	long GetBoolSummary(bool* pBGetSummary)
	{
		long lReturn = ERR_NOERROR;
		lReturn = GetValueBool("Bool", "Summary", pBGetSummary, false);
		if (lReturn == PROP_ERR_SECTION_NOT_FOUND_DEFAULT_USED)
		{
			printf_s("%s %s","Summary Bool Not Found: Default false used",EOL);
			return ERR_NOERROR;
		}
		return lReturn;
	}

	long SetBoolSkipTaxonomicGroup(bool bSetTaxonomicGroup = true)
	{
		return SetValueBool("Bool", "SkipTaxonomicGroup", bSetTaxonomicGroup);
	}

	long GetBoolSkipTaxonomicGroup(bool* pbGetTaxonomicGroup)
	{
		long lReturn = ERR_NOERROR;
		lReturn = GetValueBool("Bool", "SkipTaxonomicGroup", pbGetTaxonomicGroup, false);
		if (lReturn == PROP_ERR_SECTION_NOT_FOUND_DEFAULT_USED || lReturn == PROP_ERR_KEY_NOT_FOUND_DEFAULT_USED)
		{
			printf_s("%s %s","Skip TaxonomicGroup Bool Not Found: Default false used",EOL);
			return ERR_NOERROR;
		}
		return lReturn;
	}

	long SetBoolSkipTaxGroupFiltering(bool bSetSkipTaxGroupFiltering = true)
	{
		return SetValueBool("Bool", "SkipTaxGroupFiltering", bSetSkipTaxGroupFiltering);
	}

	long GetBoolSkipTaxGroupFiltering(bool* pbGetSkipTaxGroupFiltering)
	{
		long lReturn = ERR_NOERROR;
		lReturn = GetValueBool("Bool", "SkipTaxGroupFiltering", pbGetSkipTaxGroupFiltering, false);
		if (lReturn == PROP_ERR_SECTION_NOT_FOUND_DEFAULT_USED || lReturn == PROP_ERR_KEY_NOT_FOUND_DEFAULT_USED)
		{
			printf_s("%s %s","Skip Tax Group Filtering: Default false used",EOL);
			return ERR_NOERROR;
		}
		return lReturn;
	}

	long SetBoolOGInsteadofHOG(bool bSetOGInsteadOfHOG = true)
	{
		return SetValueBool("Bool", "OGInsteadOfHOG", bSetOGInsteadOfHOG);
	}

	long GetBoolOGInsteadofHOG(bool* pbSetOGInsteadOfHOG)
	{
		long lReturn = ERR_NOERROR;
		lReturn = GetValueBool("Bool", "OGInsteadOfHOG", pbSetOGInsteadOfHOG, false);
		if (lReturn == PROP_ERR_SECTION_NOT_FOUND_DEFAULT_USED || lReturn == PROP_ERR_KEY_NOT_FOUND_DEFAULT_USED)
		{
			printf_s("%s %s","Skip OGInsteadOfHOG: Default false used",EOL);
			return ERR_NOERROR;
		}
		return lReturn;
	}


	long SetTaxonomicGroupFilePath(const char* szTaxonomicGroupFile)
	{
		return SetValueString("Paths", "TaxonomicGroupFile", szTaxonomicGroupFile);
	}

	long GetTaxonomicGroupFilePath(std::string* pstrTaxonomicGroupFile)
	{
		return GetValueString("Paths", "TaxonomicGroupFile", pstrTaxonomicGroupFile);
	}

	long SetTaxonomicGroupThreshold(long lTaxonomicGroupThreshold) 
	{
		//Check if the value is at least 1
		if (lTaxonomicGroupThreshold < 1)
			return PARSECOMMANDLINE_TAXONOMICTHRESHOLD_TOOLOW_OSG;

		return SetValueLong("Filter", "TaxonomicGroup", lTaxonomicGroupThreshold);
	}

	long GetTaxonomicGroupThreshold(long* plTaxonomicGroupThreshold)
	{
		return GetValueLong("Filter", "TaxonomicGroup", plTaxonomicGroupThreshold, 1);
	}

	long GetTaxonomicGroupThreshold(size_t * psizeTaxonomicGroupThreshold)
	{
		long lReturn = ERR_NOERROR;
		long lTreshold = 0;
		
		lReturn = GetValueLong("Filter", "TaxonomicGroup", &lTreshold, 1);
		if (lReturn == PROP_ERR_SECTION_NOT_FOUND_DEFAULT_USED || lReturn == PROP_ERR_KEY_NOT_FOUND_DEFAULT_USED)
		{
			printf_s("%s %s", "No Threshold for Taxonomicgroup filtering: Default 1 used", EOL);
			
		}
		else if (lReturn != ERR_NOERROR)
			return lReturn;

		*psizeTaxonomicGroupThreshold = (size_t)lTreshold;

		return ERR_NOERROR;
		
	}



	long SetPhyloPyPrunerFormat()
	{
		return SetValueBool("Format", "PhyloPyPruner", true);
	}

	long GetPhyloPyPrunerFormat(bool* pbPhyloPyPrunerFormat)
	{
		long lReturn = ERR_NOERROR;
		lReturn = GetValueBool("Format", "PhyloPyPruner", pbPhyloPyPrunerFormat, false);
		if (lReturn == PROP_ERR_SECTION_NOT_FOUND_DEFAULT_USED || lReturn == PROP_ERR_KEY_NOT_FOUND_DEFAULT_USED)
		{
			printf_s("%s %s","PhyloPyPrunerFormat Bool Not Found: Default used", EOL);
			return ERR_NOERROR;
		}
		return lReturn;
	}

};