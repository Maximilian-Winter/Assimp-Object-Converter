#include "ConfigDataClass.h"


ConfigDataClass::ConfigDataClass()
{
	ConfigData.RootSections.clear();
}


ConfigDataClass::ConfigDataClass(const ConfigDataClass& other)
{
}


ConfigDataClass::~ConfigDataClass()
{
}


bool ConfigDataClass::LoadConfigDataFile(const std::string FileName)
{
	//Clear the vector with the Config Data
	ConfigData.RootSections.clear();
	std::ifstream InputFile(FileName);
	std::string InputStr;

	if (InputFile.good())
	{
		Section* CurrentSection = nullptr;
		bool HasSections = false;

		while (!InputFile.eof())
		{
			//Start to read in the Data from the File
			std::getline(InputFile, InputStr);
			RemoveCommentFromLine(InputStr);

			if (!IsOnlyWhitespacesLine(InputStr))
			{
				if (IsSectionNameLine(InputStr))
				{
					std::string SectionName = GetSectionNameFromLine(InputStr);

					if (CheckIfRootSectionExist(SectionName))
					{
						GetRootSectionByName(SectionName, CurrentSection);
					}
					else
					{
						AddSection(GetChildSectionNameListFromLine(InputStr), CurrentSection);
					}
					
					HasSections = true;
				}

				if (IsChildSectionNameLine(InputStr))
				{
					
					if (CheckIfSectionPathExist(GetChildSectionNameListFromLine(InputStr)))
					{
						GetChildBySectionPath(GetChildSectionNameListFromLine(InputStr), CurrentSection);
					}
					else
					{
						AddSection(GetChildSectionNameListFromLine(InputStr), CurrentSection);
					}
					HasSections = true;
				}

				if (IsValueLine(InputStr))
				{
					std::string ValueName = GetValueNameFromLine(InputStr);
					if(CurrentSection != nullptr)
					{
						if (IsIntValueLine(InputStr))
						{
							int Value = GetIntValueFromLine(InputStr);
							
							CurrentSection->AddIntVal(ValueName, Value);
						}

						if (IsFloatValueLine(InputStr))
						{
							float Value = GetFloatValueFromLine(InputStr);
						
							CurrentSection->AddFloatVal(ValueName, Value);
						}

						if (IsBoolValueLine(InputStr))
						{
							bool Value = GetBoolValueFromLine(InputStr);
						
							CurrentSection->AddBoolVal(ValueName, Value);
						}

						if (IsStringValueLine(InputStr))
						{
							std::string Value = GetStringValueFromLine(InputStr);
						
							CurrentSection->AddStringVal(ValueName, Value);
						}

						if (IsIntVectorLine(InputStr))
						{
							std::vector<int> Value = GetIntVectorFromLine(InputStr);

							CurrentSection->AddIntVector(ValueName, Value);
						}

						if (IsFloatVectorLine(InputStr))
						{
							std::vector<float> Value = GetFloatVectorFromLine(InputStr);

							CurrentSection->AddFloatVector(ValueName, Value);
						}
					
						if (IsBoolVectorLine(InputStr))
						{
							std::vector<bool> Value = GetBoolVectorFromLine(InputStr);

							CurrentSection->AddBoolVector(ValueName, Value);
						}

						if (IsStringVectorLine(InputStr))
						{
							std::vector<std::string> Value = GetStringVectorFromLine(InputStr);

							CurrentSection->AddStringVector(ValueName, Value);
						}
					}
				}

			}
		}
	}
	else
	{
		return false;
	}

	return true;
}


void ConfigDataClass::SaveConfigDataFile(const std::string FileName, const std::string CommentAtStartOfFile)
{
	std::ofstream fileOutput;
	fileOutput.open(FileName);

	fileOutput << "#" <<CommentAtStartOfFile << std::endl;
	fileOutput << std::endl;
	for (int k = 0; k < ConfigData.RootSections.size(); k++)
	{
		PrintSectionToFile(&ConfigData.RootSections[k], fileOutput);
	}
	fileOutput.close();
}


void ConfigDataClass::ClearConfigData()
{
	ConfigData.RootSections.clear();
}


bool ConfigDataClass::AddIntValueByName(const std::string SectionName, const std::string ValueName, int Value)
{
	Section* TempSection;

	if (IsChildSectionNameInput(SectionName))
	{
		AddSection(GetSectionNameListFromFunctionArg(SectionName), TempSection);
		return TempSection->AddIntVal(ValueName, Value);
	}
	else
	{
		return false;
	}
}


bool ConfigDataClass::AddFloatValueByName(const std::string SectionName, const std::string ValueName, float Value)
{
	Section* TempSection;

	if (IsChildSectionNameInput(SectionName))
	{
		AddSection(GetSectionNameListFromFunctionArg(SectionName), TempSection);
		return TempSection->AddFloatVal(ValueName, Value);
	}
	else
	{
		return false;
	}
}


bool ConfigDataClass::AddBoolValueByName(const std::string SectionName, const std::string ValueName, bool Value)
{
	Section* TempSection;

	if (IsChildSectionNameInput(SectionName))
	{
		AddSection(GetSectionNameListFromFunctionArg(SectionName), TempSection);
		return TempSection->AddBoolVal(ValueName, Value);
	}
	else
	{
		return false;
	}
}


bool ConfigDataClass::AddStringValueByName(const std::string SectionName, const std::string ValueName, std::string Value)
{
	Section* TempSection;

	if (IsChildSectionNameInput(SectionName))
	{
		AddSection(GetSectionNameListFromFunctionArg(SectionName), TempSection);
		return TempSection->AddStringVal(ValueName, Value);
	}
	else
	{
		return false;
	}
}


bool ConfigDataClass::AddIntVectorByName(const std::string SectionName, const std::string ValueName, std::vector<int> Value)
{
	Section* TempSection;

	if (IsChildSectionNameInput(SectionName))
	{
		AddSection(GetSectionNameListFromFunctionArg(SectionName), TempSection);
		return TempSection->AddIntVector(ValueName, Value);
	}
	else
	{
		return false;
	}
}


bool ConfigDataClass::AddFloatVectorByName(const std::string SectionName, const std::string ValueName, std::vector<float> Value)
{
	Section* TempSection;

	if (IsChildSectionNameInput(SectionName))
	{
		AddSection(GetSectionNameListFromFunctionArg(SectionName), TempSection);
		return TempSection->AddFloatVector(ValueName, Value);
	}
	else
	{
		return false;
	}
}


bool ConfigDataClass::AddBoolVectorByName(const std::string SectionName, const std::string ValueName, std::vector<bool> Value)
{
	Section* TempSection;

	if (IsChildSectionNameInput(SectionName))
	{
		AddSection(GetSectionNameListFromFunctionArg(SectionName), TempSection);
		return TempSection->AddBoolVector(ValueName, Value);
	}
	else
	{
		return false;
	}
}


bool ConfigDataClass::AddStringVectorByName(const std::string SectionName, const std::string ValueName, std::vector<std::string> Value)
{
	Section* TempSection;

	if (IsChildSectionNameInput(SectionName))
	{
		AddSection(GetSectionNameListFromFunctionArg(SectionName), TempSection);
		return TempSection->AddStringVector(ValueName, Value);
	}
	else
	{
		return false;
	}
}


int ConfigDataClass::GetNumberOfRootSections()
{
	return ConfigData.RootSections.size();
}


std::vector<int> ConfigDataClass::GetIndiciePathToRootSecton(int RootSectionIndex)
{
	std::vector<int> Indicies;
	Indicies.push_back(RootSectionIndex);

	return Indicies;
}


int ConfigDataClass::GetNumberOfAllChildSectionsFromRoot(const int RootSectionIndex)
{
	Section* Root = &ConfigData.RootSections[RootSectionIndex];

	int NumberOfChilds = 0;

	CalculateNumberOfAllChildsFromRoot(Root, NumberOfChilds);

	return NumberOfChilds;
}


bool ConfigDataClass::GetSectionName(const std::vector<int> Indicies, std::string& SectionName)
{
	Section* TempSection;
	if (GetChildByIndicieVector(Indicies, TempSection))
	{
		SectionName = TempSection->SectionName;
		return true;
	}
	else
	{
		return false;
	}
}


std::vector<int> ConfigDataClass::GetIndiciePathToChildFromRoot(const int RootSectionIndex, const int ChildIndex)
{
	std::vector<int> Indicies;

	Section* Root = &ConfigData.RootSections[RootSectionIndex];
	
	int TempChildCount = 0;

	GetChildSectionIndicieVector(Root, ChildIndex, Indicies, TempChildCount);

	return Indicies;
}


int ConfigDataClass::GetNumberOfIntValues(std::vector<int>&  Indicies)
{
	Section* TempSection;
	if (GetChildByIndicieVector(Indicies, TempSection))
	{
		return TempSection->GetNumberOfIntVals();
	}
	else
	{
		return 0;
	}
}


int ConfigDataClass::GetNumberOfIntVectors(std::vector<int>&  Indicies)
{
	Section* TempSection;
	if (GetChildByIndicieVector(Indicies, TempSection))
	{
		return TempSection->GetNumberOfIntVectors();
	}
	else
	{
		return 0;
	}
}


int ConfigDataClass::GetNumberOfFloatValues(std::vector<int>&  Indicies)
{
	Section* TempSection;
	if (GetChildByIndicieVector(Indicies, TempSection))
	{
		return TempSection->GetNumberOfFloatVals();
	}
	else
	{
		return 0;
	}
}


int ConfigDataClass::GetNumberOfFloatVectors(std::vector<int>&  Indicies)
{
	Section* TempSection;
	if (GetChildByIndicieVector(Indicies, TempSection))
	{
		return TempSection->GetNumberOfFloatVectors();
	}
	else
	{
		return 0;
	}
}


int ConfigDataClass::GetNumberOfBoolValues(std::vector<int>&  Indicies)
{
	Section* TempSection;
	if (GetChildByIndicieVector(Indicies, TempSection))
	{
		return TempSection->GetNumberOfBoolVals();
	}
	else
	{
		return 0;
	}
}


int ConfigDataClass::GetNumberOfBoolVectors(std::vector<int>&  Indicies)
{
	Section* TempSection;
	if (GetChildByIndicieVector(Indicies, TempSection))
	{
		return TempSection->GetNumberOfBoolVectors();
	}
	else
	{
		return 0;
	}

}


int ConfigDataClass::GetNumberOfStringValues(std::vector<int>&  Indicies)
{
	Section* TempSection;
	if (GetChildByIndicieVector(Indicies, TempSection))
	{
		return TempSection->GetNumberOfStringVals();
	}
	else
	{
		return 0;
	}
}


int ConfigDataClass::GetNumberOfStringVectors(std::vector<int>&  Indicies)
{
	Section* TempSection;
	if (GetChildByIndicieVector(Indicies, TempSection))
	{
		return TempSection->GetNumberOfStringVectors();
	}
	else
	{
		return 0;
	}
}


bool ConfigDataClass::GetIntValueNameByIndex(const std::vector<int>& Indicies, const int ValueIndex, std::string& ValueName)
{
	Section* TempSection;
	if (GetChildByIndicieVector(Indicies, TempSection))
	{
		return TempSection->GetIntValName(ValueIndex, ValueName);
	}
	else
	{
		return false;

	}
}


bool ConfigDataClass::GetIntValueByIndex(const std::vector<int>& Indicies, const int ValueIndex, int& Value)
{
	Section* TempSection;
	if (GetChildByIndicieVector(Indicies, TempSection))
	{
		return TempSection->GetIntVal(ValueIndex, Value);
	}
	else
	{
		return false;

	}
}


bool ConfigDataClass::GetIntValueByName(const std::string SectionName, const std::string ValueName, int& Value)
{
	Section* TempSection;

	if (IsChildSectionNameInput(SectionName))
	{
		if (GetChildBySectionPath(GetSectionNameListFromFunctionArg(SectionName), TempSection))
		{
			return TempSection->GetIntVal(ValueName, Value);
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}


bool ConfigDataClass::GetIntVectorNameByIndex(const std::vector<int>& Indicies, const int ValueIndex, std::string& ValueName)
{
	Section* TempSection;
	if (GetChildByIndicieVector(Indicies, TempSection))
	{
		return TempSection->GetIntVectorName(ValueIndex, ValueName);
	}
	else
	{
		return false;
	}
}


bool ConfigDataClass::GetIntVectorByIndex(const std::vector<int>& Indicies, const int ValueIndex, std::vector<int>& Value)
{
	Section* TempSection;
	if (GetChildByIndicieVector(Indicies, TempSection))
	{
		return TempSection->GetIntVector(ValueIndex, Value);
	}
	else
	{
		return false;
	}
}


bool ConfigDataClass::GetIntVectorByName(const std::string SectionName, const std::string ValueName, std::vector<int> &Value)
{
	Section* TempSection;

	if (IsChildSectionNameInput(SectionName))
	{
		if (GetChildBySectionPath(GetSectionNameListFromFunctionArg(SectionName), TempSection))
		{
			return TempSection->GetIntVector(ValueName, Value);
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}


bool ConfigDataClass::GetFloatValueNameByIndex(const std::vector<int>& Indicies, const int ValueIndex, std::string& ValueName)
{
	Section* TempSection;
	if (GetChildByIndicieVector(Indicies, TempSection))
	{
		return TempSection->GetFloatValName(ValueIndex, ValueName);
	}
	else
	{
		return false;
	}
}


bool ConfigDataClass::GetFloatValueByIndex(const std::vector<int>& Indicies, const int ValueIndex, float& Value)
{
	Section* TempSection;
	if (GetChildByIndicieVector(Indicies, TempSection))
	{
		return TempSection->GetFloatVal(ValueIndex, Value);
	}
	else
	{
		return false;
	}
}


bool ConfigDataClass::GetFloatValueByName(const std::string SectionName, const std::string ValueName, float& Value)
{
	Section* TempSection;

	if (IsChildSectionNameInput(SectionName))
	{
		if (GetChildBySectionPath(GetSectionNameListFromFunctionArg(SectionName), TempSection))
		{
			return TempSection->GetFloatVal(ValueName, Value);
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}


bool ConfigDataClass::GetFloatVectorNameByIndex(const std::vector<int>& Indicies, const int ValueIndex, std::string& ValueName)
{
	Section* TempSection;
	if (GetChildByIndicieVector(Indicies, TempSection))
	{
		return TempSection->GetFloatVectorName(ValueIndex, ValueName);
	}
	else
	{
		return false;
	}
}


bool ConfigDataClass::GetFloatVectorByIndex(const std::vector<int>& Indicies, const int ValueIndex, std::vector<float>& Value)
{
	Section* TempSection;
	if (GetChildByIndicieVector(Indicies, TempSection))
	{
		return TempSection->GetFloatVector(ValueIndex, Value);
	}
	else
	{
		return false;
	}
}


bool ConfigDataClass::GetFloatVectorByName(const std::string SectionName, const std::string ValueName, std::vector<float> &Value)
{
	Section* TempSection;

	if (IsChildSectionNameInput(SectionName))
	{
		if (GetChildBySectionPath(GetSectionNameListFromFunctionArg(SectionName), TempSection))
		{
			return TempSection->GetFloatVector(ValueName, Value);
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}


bool ConfigDataClass::GetBoolValueNameByIndex(const std::vector<int>& Indicies, const int ValueIndex, std::string& ValueName)
{
	Section* TempSection;
	if (GetChildByIndicieVector(Indicies, TempSection))
	{
		return TempSection->GetBoolValName(ValueIndex, ValueName);
	}
	else
	{
		return false;
	}
}


bool ConfigDataClass::GetBoolValueByIndex(const std::vector<int>& Indicies, const int ValueIndex, bool& Value)
{
	Section* TempSection;
	if (GetChildByIndicieVector(Indicies, TempSection))
	{
		return TempSection->GetBoolVal(ValueIndex, Value);
	}
	else
	{
		return false;
	}
}


bool ConfigDataClass::GetBoolValueByName(const std::string SectionName, const std::string ValueName, bool& Value)
{
	Section* TempSection;

	if (IsChildSectionNameInput(SectionName))
	{
		if (GetChildBySectionPath(GetSectionNameListFromFunctionArg(SectionName), TempSection))
		{
			return TempSection->GetBoolVal(ValueName, Value);
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}


bool ConfigDataClass::GetBoolVectorNameByIndex(const std::vector<int>& Indicies, const int ValueIndex, std::string& ValueName)
{
	Section* TempSection;
	if (GetChildByIndicieVector(Indicies, TempSection))
	{
		return TempSection->GetBoolVectorName(ValueIndex, ValueName);
	}
	else
	{
		return false;
	}
}


bool ConfigDataClass::GetBoolVectorByIndex(const std::vector<int>& Indicies, const int ValueIndex, std::vector<bool> &Value)
{

	Section* TempSection;
	if (GetChildByIndicieVector(Indicies, TempSection))
	{
		return TempSection->GetBoolVector(ValueIndex, Value);
	}
	else
	{
		return false;
	}
}


bool ConfigDataClass::GetBoolVectorByName(const std::string SectionName, const std::string ValueName, std::vector<bool> &Value)
{
	Section* TempSection;

	if (IsChildSectionNameInput(SectionName))
	{
		if (GetChildBySectionPath(GetSectionNameListFromFunctionArg(SectionName), TempSection))
		{
			return TempSection->GetBoolVector(ValueName, Value);
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}


bool ConfigDataClass::GetStringValueNameByIndex(const std::vector<int>& Indicies, const int ValueIndex, std::string& ValueName)
{
	Section* TempSection;
	if (GetChildByIndicieVector(Indicies, TempSection))
	{
		return TempSection->GetStringValName(ValueIndex, ValueName);
	}
	else
	{
		return false;
	}
}


bool ConfigDataClass::GetStringValueByIndex(const std::vector<int>& Indicies, const int ValueIndex, std::string& Value)
{
	Section* TempSection;
	if (GetChildByIndicieVector(Indicies, TempSection))
	{
		return TempSection->GetStringVal(ValueIndex, Value);
	}
	else
	{
		return false;
	}
}


bool ConfigDataClass::GetStringValueByName(const std::string SectionName, const std::string ValueName, std::string& Value)
{
	Section* TempSection;

	if (IsChildSectionNameInput(SectionName))
	{
		if (GetChildBySectionPath(GetSectionNameListFromFunctionArg(SectionName), TempSection))
		{
			return TempSection->GetStringVal(ValueName, Value);
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}


bool ConfigDataClass::GetStringVectorNameByIndex(const std::vector<int>& Indicies, const int ValueIndex, std::string& ValueName)
{
	Section* TempSection;
	if (GetChildByIndicieVector(Indicies, TempSection))
	{
		return TempSection->GetStringVectorName(ValueIndex, ValueName);
	}
	else
	{
		return false;
	}
}


bool ConfigDataClass::GetStringVectorByIndex(const std::vector<int>& Indicies, const int ValueIndex, std::vector<std::string> &Value)
{
	Section* TempSection;
	if (GetChildByIndicieVector(Indicies, TempSection))
	{
		return TempSection->GetStringVector(ValueIndex, Value);
	}
	else
	{
		return false;
	}
}


bool ConfigDataClass::GetStringVectorByName(const std::string SectionName, const std::string ValueName, std::vector<std::string> &Value)
{
	Section* TempSection;

	if (IsChildSectionNameInput(SectionName))
	{
		if (GetChildBySectionPath(GetSectionNameListFromFunctionArg(SectionName), TempSection))
		{
			return TempSection->GetStringVector(ValueName, Value);
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}


bool ConfigDataClass::AddSection(std::vector<std::string> SectionPathList, Section*& AddedSection)
{
	Section* TempSection;

	if (GetRootSectionByName(SectionPathList[0], TempSection))
	{
		Section* ChildTempSection = TempSection;

		std::vector<int> TempIndicies;

		int RootIndex;
		GetRootSectionIndex(SectionPathList[0], RootIndex);

		TempIndicies.push_back(RootIndex);

		for (int SectionNameListIndex = 1; SectionNameListIndex < SectionPathList.size(); SectionNameListIndex++)
		{
			Section* TempSection = nullptr;
			if (CheckIfChildSectionExist(ChildTempSection, SectionPathList[SectionNameListIndex]))
			{
				GetChildSectionFromParent(ChildTempSection, SectionPathList[SectionNameListIndex], TempSection);
				ChildTempSection = TempSection;

				TempIndicies = ChildTempSection->SectionIndiciePath;
			}
			else
			{
				Section Temp(SectionPathList[SectionNameListIndex]);

				TempIndicies.push_back(ChildTempSection->ChildSections.size());

				for (int k = 0; k <= SectionNameListIndex; k++)
				{
					Temp.SectionPath.push_back(SectionPathList[k]);
				}

				for (int k = 0; k < TempIndicies.size(); k++)
				{
					Temp.SectionIndiciePath.push_back(TempIndicies[k]);
				}

				ChildTempSection->ChildSections.push_back(Temp);

				ChildTempSection = &ChildTempSection->ChildSections[ChildTempSection->ChildSections.size() - 1];

			}
		}

		AddedSection = ChildTempSection;
	}
	else
	{
		ConfigData.RootSections.push_back(Section(SectionPathList[0]));

		Section* ChildTempSection = &ConfigData.RootSections[ConfigData.RootSections.size() - 1];
		std::vector<int> TempIndicies;
		int RootIndex;
		ChildTempSection->SectionPath.push_back(SectionPathList[0]);

		GetRootSectionIndex(SectionPathList[0], RootIndex);

		TempIndicies.push_back(RootIndex);
		for (int SectionNameListIndex = 1; SectionNameListIndex < SectionPathList.size(); SectionNameListIndex++)
		{
			Section* TempSection = nullptr;
			if (CheckIfChildSectionExist(ChildTempSection, SectionPathList[SectionNameListIndex]))
			{
				GetChildSectionFromParent(ChildTempSection, SectionPathList[SectionNameListIndex], TempSection);
				ChildTempSection = TempSection;

				TempIndicies = ChildTempSection->SectionIndiciePath;
			}
			else
			{
				Section Temp(SectionPathList[SectionNameListIndex]);

				TempIndicies.push_back(ChildTempSection->ChildSections.size());

				for (int k = 0; k < SectionNameListIndex; k++)
				{
					Temp.SectionPath.push_back(SectionPathList[k]);
				}

				for (int k = 0; k < TempIndicies.size(); k++)
				{
					Temp.SectionIndiciePath.push_back(TempIndicies[k]);
				}

				ChildTempSection->ChildSections.push_back(Temp);

				ChildTempSection = &ChildTempSection->ChildSections[ChildTempSection->ChildSections.size() - 1];

			}
		}
		AddedSection = ChildTempSection;
	}

	return true;
}


bool ConfigDataClass::GetRootSectionByName(std::string SectionName, Section*& RootSection)
{
	int SectionIndex = -1;
	for (int i = 0; i < ConfigData.RootSections.size(); i++)
	{
		if (ConfigData.RootSections[i].SectionName == SectionName)
		{
			SectionIndex = i;
		}
	}
	if (SectionIndex == -1)
	{
		RootSection = nullptr;
		return false;
	}

	RootSection = &ConfigData.RootSections[SectionIndex];

	return true;
}


bool ConfigDataClass::GetRootSectionIndex(std::string SectionName, int& RootSectionIndex)
{
	int SectionIndex = -1;
	for (int i = 0; i < ConfigData.RootSections.size(); i++)
	{
		if (ConfigData.RootSections[i].SectionName == SectionName)
		{
			SectionIndex = i;
		}
	}
	if (SectionIndex == -1)
	{
		return false;
	}

	RootSectionIndex = SectionIndex;

	return true;
}


bool ConfigDataClass::GetChildSectionFromParent(Section* ParentSection, std::string SectionName, Section*& ChildSection)
{
	ChildSection = nullptr;

	int SectionIndex = -1;
	for (int i = 0; i < ParentSection->ChildSections.size(); i++)
	{
		if (ParentSection->ChildSections[i].SectionName == SectionName)
		{
			SectionIndex = i;
		}
	}
	if (SectionIndex == -1)
	{
		return nullptr;
	}

	ChildSection = &ParentSection->ChildSections[SectionIndex];

	return true;
}


void ConfigDataClass::GetChildByIndex(Section* RootSection, int Index, Section*& ChildSection)
{
	ChildSection = &RootSection->ChildSections[Index];
}


bool ConfigDataClass::GetChildBySectionPath(std::vector<std::string> SectionPath, Section*& ChildSection)
{
	Section* RootTempSection;

	if (GetRootSectionByName(SectionPath[0], RootTempSection))
	{
		Section* ChildTempSection = RootTempSection;

		if (SectionPath.size() == 1)
		{
			ChildSection = RootTempSection;
			return true;
		}

		for (int SectionNameListIndex = 1; SectionNameListIndex < SectionPath.size(); SectionNameListIndex++)
		{
			Section* TempSection = nullptr;
			if (CheckIfChildSectionExist(ChildTempSection, SectionPath[SectionNameListIndex]))
			{
				GetChildSectionFromParent(ChildTempSection, SectionPath[SectionNameListIndex], TempSection);
				ChildTempSection = TempSection;

				ChildSection = ChildTempSection;
			}
			else
			{
				return false;
			}
		}


	}
	else
	{
		return false;
	}

	return true;
}


void ConfigDataClass::GetChildSectionIndicieVector(Section* RootSection, const int ChildIndex, std::vector<int>& Indicies, int& ChildCount)
{
	for (int i = 0; i < RootSection->ChildSections.size(); i++)
	{
		if (ChildCount == ChildIndex)
		{
			ChildCount++;
			Indicies = RootSection->ChildSections[i].SectionIndiciePath;
			i = RootSection->ChildSections.size();
		}
		else
		{
			ChildCount++;
			GetChildSectionIndicieVector(&RootSection->ChildSections[i], ChildIndex, Indicies, ChildCount);
		}
		
	}
}


bool ConfigDataClass::GetChildByIndicieVector(const std::vector<int>& Indicies, Section*& ChildSection)
{
	if (Indicies[0] < ConfigData.RootSections.size())
	{
		Section* TempSection = &ConfigData.RootSections[Indicies[0]];

		if (Indicies.size() == 1)
		{
			ChildSection = TempSection;
			return true;
		}

		for (int i = 1; i < Indicies.size(); i++)
		{
			if (i == Indicies.size() - 1)
			{
				if (Indicies[i] < TempSection->ChildSections.size())
				{
					GetChildByIndex(TempSection, Indicies[i], ChildSection);
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				if (Indicies[i] < TempSection->ChildSections.size())
				{
					GetChildByIndex(TempSection, Indicies[i], TempSection);
				}
				else
				{
					return false;
				}
			}
		}
	}
	else
	{
		return false;
	}
}


void ConfigDataClass::CalculateNumberOfAllChildsFromRoot(Section* RootSection, int& NumberOfChildSections)
{
	for (int i = 0; i < RootSection->ChildSections.size(); i++)
	{
		CalculateNumberOfAllChildsFromRoot(&RootSection->ChildSections[i], NumberOfChildSections);
		NumberOfChildSections++;
	}
	
}


bool  ConfigDataClass::CheckIfRootSectionExist(std::string SectionName)
{
	int SectionIndex = -1;
	for (int i = 0; i < ConfigData.RootSections.size(); i++)
	{
		if (ConfigData.RootSections[i].SectionName == SectionName)
		{
			SectionIndex = i;
		}
	}
	return !(SectionIndex == -1);
}


bool ConfigDataClass::CheckIfChildSectionExist(Section* ParentSection, std::string SectionName)
{
	int SectionIndex = -1;

	for (int i = 0; i < ParentSection->ChildSections.size(); i++)
	{
		if (ParentSection->ChildSections[i].SectionName == SectionName)
		{
			SectionIndex = i;
		}
	}

	if (SectionIndex == -1)
	{
		return false;
	}

	return !(SectionIndex == -1);
}


bool ConfigDataClass::CheckIfSectionPathExist(std::vector<std::string> SectionPath)
{
	Section* RootTempSection;

	if (GetRootSectionByName(SectionPath[0], RootTempSection))
	{
		Section* ChildTempSection = RootTempSection;

		for (int SectionNameListIndex = 1; SectionNameListIndex < SectionPath.size(); SectionNameListIndex++)
		{
			Section* TempSection = nullptr;
			if (CheckIfChildSectionExist(ChildTempSection, SectionPath[SectionNameListIndex]))
			{
				GetChildSectionFromParent(ChildTempSection, SectionPath[SectionNameListIndex], TempSection);
				ChildTempSection = TempSection;
			}
			else
			{
				return false;
			}
		}


	}
	else
	{
		return false;
	}

	return true;
}


void ConfigDataClass::PrintSectionToFile(Section* SectionData, std::ofstream& OutputFile)
{

		for (int i = 0; i < SectionData->SectionPath.size(); i++)
		{
			if (i == SectionData->SectionPath.size() - 1)
			{
				OutputFile << "[" << SectionData->SectionPath[i] << "]";
			}
			else
			{
				OutputFile << "[" << SectionData->SectionPath[i] << "].";
			}
		}

		OutputFile << std::endl;

		for (int i = 0; i < SectionData->IntVals.size(); i++)
		{
			int Val = SectionData->IntVals[i].Val;
			std::string ValName = SectionData->IntVals[i].Name;

			OutputFile << ValName << " = " << Val << std::endl;
		}

		for (int i = 0; i < SectionData->FloatVals.size(); i++)
		{
			float Val = SectionData->FloatVals[i].Val;
			std::string ValName = SectionData->FloatVals[i].Name;

			OutputFile << ValName << " = " << Val << std::endl;
		}

		for (int i = 0; i < SectionData->BoolVals.size(); i++)
		{
			bool Val = SectionData->BoolVals[i].Val;
			std::string ValName = SectionData->BoolVals[i].Name;

			OutputFile << ValName << " = " << Val << std::endl;
		}

		for (int i = 0; i < SectionData->StringVals.size(); i++)
		{
			std::string Val = SectionData->StringVals[i].Val;
			std::string ValName = SectionData->StringVals[i].Name;

			OutputFile << ValName << " = \"" << Val << "\"" << std::endl;
		}

		for (int i = 0; i < SectionData->IntVectors.size(); i++)
		{
			std::vector<int> Val = SectionData->IntVectors[i].Val;
			std::string ValName = SectionData->IntVectors[i].Name;

			OutputFile << ValName << " = { ";
			for (int t = 0; t < Val.size(); t++)
			{
				if (t == Val.size() - 1)
				{
					OutputFile << Val[t];
				}
				else
				{
					OutputFile << Val[t] << ", ";
				}
			}
			OutputFile << " }" << std::endl;

		}

		for (int i = 0; i <  SectionData->FloatVectors.size(); i++)
		{
			std::vector<float> Val = SectionData->FloatVectors[i].Val;
			std::string ValName = SectionData->FloatVectors[i].Name;

			OutputFile << ValName << " = { ";
			for (int t = 0; t < Val.size(); t++)
			{
				if (t == Val.size() - 1)
				{
					OutputFile << Val[t];
				}
				else
				{
					OutputFile << Val[t] << ", ";
				}
			}
			OutputFile << " }" << std::endl;

		}

		for (int i = 0; i < SectionData->BoolVectors.size(); i++)
		{
			std::vector<bool> Val = SectionData->BoolVectors[i].Val;
			std::string ValName = SectionData->BoolVectors[i].Name;

			OutputFile << ValName << " = { ";
			for (int t = 0; t < Val.size(); t++)
			{
				if (t == Val.size() - 1)
				{
					OutputFile << Val[t];
				}
				else
				{
					OutputFile << Val[t] << ", ";
				}
			}
			OutputFile << " }" << std::endl;


		}

		for (int i = 0; i < SectionData->StringVectors.size(); i++)
		{
			std::vector<std::string> Val = SectionData->StringVectors[i].Val;
			std::string ValName = SectionData->StringVectors[i].Name;

			OutputFile << ValName << " = { ";
			for (int t = 0; t < Val.size(); t++)
			{
				if (t == Val.size() - 1)
				{
					OutputFile << "\"" << Val[t] << "\"";
				}
				else
				{
					OutputFile << "\"" << Val[t] << "\"" << ", ";
				}
			}
			OutputFile << " }" << std::endl;
		}

		OutputFile << std::endl;

		for (int k = 0; k < SectionData->ChildSections.size(); k++)
		{
			PrintSectionToFile(&SectionData->ChildSections[k], OutputFile);
		}

}