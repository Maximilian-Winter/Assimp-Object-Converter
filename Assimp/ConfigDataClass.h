// Filename: ConfigDataClass.h
// Date: 07.06.2015
// Author: Maximilian Winter
#ifndef _CONFIGDATACLASS_H_
#define _CONFIGDATACLASS_H_


//Includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>
#include <vector>
#include <algorithm>


// Class name: ConfigDataClass

class ConfigDataClass
{
private:
	//Data Structures for the Configfile
	struct IntValue
	{
		IntValue(std::string ValName, int Value)
		{
			Name = ValName;
			Val = Value;
		}
		std::string Name;
		int Val;
	};

	struct IntVector
	{
		IntVector(std::string ValName, std::vector<int> Value)
		{
			Name = ValName;
			Val = Value;
		}
		std::string Name;
		std::vector<int> Val;
	};

	struct FloatValue
	{
		FloatValue(std::string ValName, float Value)
		{
			Name = ValName;
			Val = Value;
		}
		std::string Name;
		float Val;
	};

	struct FloatVector
	{
		FloatVector(std::string ValName, std::vector<float> Value)
		{
			Name = ValName;
			Val = Value;
		}
		std::string Name;
		std::vector<float> Val;
	};

	struct BoolValue
	{
		BoolValue(std::string ValName, bool Value)
		{
			Name = ValName;
			Val = Value;
		}
		std::string Name;
		bool Val;
	};

	struct BoolVector
	{
		BoolVector(std::string ValName, std::vector<bool> Value)
		{
			Name = ValName;
			Val = Value;
		}
		std::string Name;
		std::vector<bool> Val;
	};

	struct StringValue
	{
		StringValue(std::string ValName, std::string Value)
		{
			Name = ValName;
			Val = Value;
		}
		std::string Name;
		std::string Val;
	};

	struct StringVector
	{
		StringVector(std::string ValName, std::vector<std::string> Value)
		{
			Name = ValName;
			Val = Value;
		}
		std::string Name;
		std::vector<std::string> Val;
	};


	struct Section
	{

		Section()
		{
			SectionName = "";
			SectionPath.clear();
			SectionIndiciePath.clear();

			IntVals.clear();
			IntVectors.clear();
			FloatVals.clear();
			FloatVectors.clear();
			BoolVals.clear();
			BoolVectors.clear();
			StringVals.clear();
			StringVectors.clear();

			ChildSections.clear();

		};

		Section(std::string sectionName)
		{
			SectionName = sectionName;
			SectionPath.clear();
			SectionIndiciePath.clear();

			IntVals.clear();
			IntVectors.clear();
			FloatVals.clear();
			FloatVectors.clear();
			BoolVals.clear();
			BoolVectors.clear();
			StringVals.clear();
			StringVectors.clear();

			ChildSections.clear();

		}

		bool AddIntVal(std::string ValueName, int Val)
		{
			if (!CheckIfIntValueExist(ValueName))
			{
				IntVals.push_back(IntValue(ValueName, Val));
			}
			else
			{
				return false;
			}

			return true;
				
		}

		bool AddFloatVal(std::string ValueName, float Val)
		{
			if (!CheckIfFloatValueExist(ValueName))
			{
				FloatVals.push_back(FloatValue(ValueName, Val));
			}
			else
			{
				return false;
			}

			return true;
		}

		bool AddBoolVal(std::string ValueName, bool Val)
		{
			if (!CheckIfBoolValueExist(ValueName))
			{
				BoolVals.push_back(BoolValue(ValueName, Val));
			}
			else
			{
				return false;
			}

			return true;
		}

		bool AddStringVal(std::string ValueName, std::string Val)
		{
			if (!CheckIfStringValueExist(ValueName))
			{
				StringVals.push_back(StringValue(ValueName, Val));
			}
			else
			{
				return false;
			}

			return true;
		}

		bool AddIntVector(std::string ValueName, std::vector<int> Val)
		{
			if (!CheckIfIntVectorExist(ValueName))
			{
				IntVectors.push_back(IntVector(ValueName, Val));
			}
			else
			{
				return false;
			}

			return true;
		}

		bool AddFloatVector(std::string ValueName, std::vector<float> Val)
		{
			if (!CheckIfFloatVectorExist(ValueName))
			{
				FloatVectors.push_back(FloatVector(ValueName, Val));
			}
			else
			{
				return false;
			}

			return true;
		}

		bool AddBoolVector(std::string ValueName, std::vector<bool> Val)
		{
			if (!CheckIfBoolVectorExist(ValueName))
			{
				BoolVectors.push_back(BoolVector(ValueName, Val));
			}
			else
			{
				return false;
			}

			return true;
		}

		bool AddStringVector(std::string ValueName, std::vector< std::string> Val)
		{
			if (!CheckIfStringVectorExist(ValueName))
			{
				StringVectors.push_back(StringVector(ValueName, Val));
			}
			else
			{
				return false;
			}

			return true;
		}

		bool GetIntVal(std::string ValueName, int& Value)
		{
			bool FoundValue = false;

			for (IntValue it : IntVals)
			{
				if (it.Name == ValueName)
				{
					Value = it.Val;
					FoundValue = true;
				}
			}

			return FoundValue;
		}
		bool GetIntVal(int Index, int& Value)
		{
			bool FoundValue = false;

			if (Index < IntVals.size())
			{
				Value = IntVals[Index].Val;
				FoundValue = true;
			}

			return FoundValue;
		}
		bool GetIntValName(int Index, std::string& ValueName)
		{
			bool FoundValue = false;

			if (Index < IntVals.size())
			{
				ValueName = IntVals[Index].Name;
				FoundValue = true;
			}

			return FoundValue;
		}

		bool GetIntVector(std::string ValueName, std::vector<int>& Value)
		{
			bool FoundValue = false;

			for (IntVector it : IntVectors)
			{
				if (it.Name == ValueName)
				{
					Value = it.Val;
					FoundValue = true;
				}
			}

			return FoundValue;
		}
		bool GetIntVector(int Index, std::vector<int>& Value)
		{
			bool FoundValue = false;

			if (Index < IntVectors.size())
			{
				Value = IntVectors[Index].Val;
				FoundValue = true;
			}

			return FoundValue;
		}
		bool GetIntVectorName(int Index, std::string& ValueName)
		{
			bool FoundValue = false;

			if (Index < IntVectors.size())
			{
				ValueName = IntVectors[Index].Name;
				FoundValue = true;
			}

			return FoundValue;
		}

		bool GetFloatVal(std::string ValueName, float& Value)
		{
			bool FoundValue = false;

			for (FloatValue it : FloatVals)
			{
				if (it.Name == ValueName)
				{
					Value = it.Val;
					FoundValue = true;
				}
			}

			return FoundValue;
		}
		bool GetFloatVal(int Index, float& Value)
		{
			bool FoundValue = false;

			if (Index < FloatVals.size())
			{
				Value = FloatVals[Index].Val;
				FoundValue = true;
			}

			return FoundValue;
		}
		bool GetFloatValName(int Index, std::string& ValueName)
		{
			bool FoundValue = false;

			if (Index < FloatVals.size())
			{
				ValueName = FloatVals[Index].Name;
				FoundValue = true;
			}

			return FoundValue;
		}

		bool GetFloatVector(std::string ValueName, std::vector<float>& Value)
		{
			bool FoundValue = false;

			for (FloatVector it : FloatVectors)
			{
				if (it.Name == ValueName)
				{
					Value = it.Val;
					FoundValue = true;
				}
			}

			return FoundValue;
		}
		bool GetFloatVector(int Index, std::vector<float>& Value)

		{
			bool FoundValue = false;

			if (Index < FloatVectors.size())
			{
				Value = FloatVectors[Index].Val;
				FoundValue = true;
			}

			return FoundValue;
		}
		bool GetFloatVectorName(int Index, std::string& ValueName)
		{
			bool FoundValue = false;

			if (Index < FloatVectors.size())
			{
				ValueName = FloatVectors[Index].Name;
				FoundValue = true;
			}

			return FoundValue;
		}

		bool GetBoolVal(std::string ValueName, bool& Value)
		{
			bool FoundValue = false;

			for (BoolValue it : BoolVals)
			{
				if (it.Name == ValueName)
				{
					Value = it.Val;
					FoundValue = true;
				}
			}

			return FoundValue;
		}
		bool GetBoolVal(int Index, bool& Value)
		{
			bool FoundValue = false;

			if (Index < BoolVals.size())
			{
				Value = BoolVals[Index].Val;
				FoundValue = true;
			}

			return FoundValue;
		}
		bool GetBoolValName(int Index, std::string& ValueName)
		{
			bool FoundValue = false;

			if (Index < BoolVals.size())
			{
				ValueName = BoolVals[Index].Name;
				FoundValue = true;
			}

			return FoundValue;
		}

		bool GetBoolVector(std::string ValueName, std::vector<bool>& Value)
		{
			bool FoundValue = false;

			for (BoolVector it : BoolVectors)
			{
				if (it.Name == ValueName)
				{
					Value = it.Val;
					FoundValue = true;
				}
			}

			return FoundValue;
		}
		bool GetBoolVector(int Index, std::vector<bool>& Value)
		{
			bool FoundValue = false;

			if (Index < BoolVectors.size())
			{
				Value = BoolVectors[Index].Val;
				FoundValue = true;
			}

			return FoundValue;
		}
		bool GetBoolVectorName(int Index, std::string& ValueName)
		{
			bool FoundValue = false;

			if (Index < BoolVectors.size())
			{
				ValueName = BoolVectors[Index].Name;
				FoundValue = true;
			}

			return FoundValue;
		}

		bool GetStringVal(std::string ValueName, std::string& Value)
		{
			bool FoundValue = false;

			for (StringValue it : StringVals)
			{
				if (it.Name == ValueName)
				{
					Value = it.Val;
					FoundValue = true;
				}
			}

			return FoundValue;
		}
		bool GetStringVal(int Index, std::string& Value)
		{
			bool FoundValue = false;

			if (Index < StringVals.size())
			{
				Value = StringVals[Index].Val;
				FoundValue = true;
			}

			return FoundValue;
		}
		bool GetStringValName(int Index, std::string& ValueName)
		{
			bool FoundValue = false;

			if (Index < StringVals.size())
			{
				ValueName = StringVals[Index].Name;
				FoundValue = true;
			}

			return FoundValue;
		}

		bool GetStringVector(std::string ValueName, std::vector<std::string>& Value)
		{
			bool FoundValue = false;

			for (StringVector it : StringVectors)
			{
				if (it.Name == ValueName)
				{
					Value = it.Val;
					FoundValue = true;
				}
			}

			return FoundValue;
		}
		bool GetStringVector(int Index, std::vector<std::string>& Value)
		{
			bool FoundValue = false;

			if (Index < StringVectors.size())
			{
				Value = StringVectors[Index].Val;
				FoundValue = true;
			}

			return FoundValue;
		}
		bool GetStringVectorName(int Index, std::string& ValueName)
		{
			bool FoundValue = false;

			if (Index < StringVectors.size())
			{
				ValueName = StringVectors[Index].Name;
				FoundValue = true;
			}

			return FoundValue;
		}

		int GetNumberOfIntVals()
		{
			return IntVals.size();
		}
		int GetNumberOfIntVectors()
		{
			return IntVectors.size();
		}

		int GetNumberOfFloatVals()
		{
			return FloatVals.size();
		}
		int GetNumberOfFloatVectors()
		{
			return FloatVectors.size();
		}

		int GetNumberOfBoolVals()
		{
			return BoolVals.size();
		}
		int GetNumberOfBoolVectors()
		{
			return BoolVectors.size();
		}

		int GetNumberOfStringVals()
		{
			return StringVals.size();
		}
		int GetNumberOfStringVectors()
		{
			return StringVectors.size();
		}

		bool CheckIfValueExist(std::string ValueName)
		{

			for (int i = 0; i < BoolVals.size(); i++)
			{
				if (BoolVals[i].Name == ValueName)
				{
					return true;
				}
			}

			for (int i = 0; i < BoolVectors.size(); i++)
			{
				if (BoolVectors[i].Name == ValueName)
				{
					return true;
				}
			}

			for (int i = 0; i < FloatVals.size(); i++)
			{
				if (FloatVals[i].Name == ValueName)
				{
					return true;
				}
			}

			for (int i = 0; i < FloatVectors.size(); i++)
			{
				if (FloatVectors[i].Name == ValueName)
				{
					return true;
				}
			}

			for (int i = 0; i < IntVals.size(); i++)
			{
				if (IntVals[i].Name == ValueName)
				{
					return true;
				}
			}

			for (int i = 0; i < IntVectors.size(); i++)
			{
				if (IntVectors[i].Name == ValueName)
				{
					return true;
				}
			}

			for (int i = 0; i < StringVals.size(); i++)
			{
				if (StringVals[i].Name == ValueName)
				{
					return true;
				}
			}

			for (int i = 0; i < StringVectors.size(); i++)
			{
				if (StringVectors[i].Name == ValueName)
				{
					return true;
				}
			}

			return false;
		}
		bool CheckIfIntValueExist(std::string ValueName)
		{
			for (int i = 0; i < IntVals.size(); i++)
			{
				if (IntVals[i].Name == ValueName)
				{
					return true;
				}
			}
			return false;
		}
		bool CheckIfIntVectorExist(std::string ValueName)
		{
			for (int i = 0; i < IntVectors.size(); i++)
			{
				if (IntVectors[i].Name == ValueName)
				{
					return true;
				}
			}
			return false;
		}
		bool CheckIfFloatValueExist(std::string ValueName)
		{
			for (int i = 0; i < FloatVals.size(); i++)
			{
				if (FloatVals[i].Name == ValueName)
				{
					return true;
				}
			}
			return false;
		}
		bool CheckIfFloatVectorExist(std::string ValueName)
		{
			for (int i = 0; i < FloatVectors.size(); i++)
			{
				if (FloatVectors[i].Name == ValueName)
				{
					return true;
				}
			}
			return false;
		}
		bool CheckIfBoolValueExist(std::string ValueName)
		{
			for (int i = 0; i < BoolVals.size(); i++)
			{
				if (BoolVals[i].Name == ValueName)
				{
					return true;
				}
			}
			return false;
		}
		bool CheckIfBoolVectorExist(std::string ValueName)
		{
			for (int i = 0; i < BoolVectors.size(); i++)
			{
				if (BoolVectors[i].Name == ValueName)
				{
					return true;
				}
			}
			return false;
		}
		bool CheckIfStringValueExist(std::string ValueName)
		{
			for (int i = 0; i < StringVals.size(); i++)
			{
				if (StringVals[i].Name == ValueName)
				{
					return true;
				}
			}
			return false;
		}
		bool CheckIfStringVectorExist(std::string ValueName)
		{
			for (int i = 0; i < StringVectors.size(); i++)
			{
				if (StringVectors[i].Name == ValueName)
				{
					return true;
				}
			}
			return false;
		}

		bool GetChildSection(std::string SectionName)
		{
			
		}

		std::string SectionName;
		std::vector<std::string> SectionPath;
		std::vector<int> SectionIndiciePath;

		std::vector<IntValue> IntVals;
		std::vector<IntVector> IntVectors;
		std::vector<FloatValue> FloatVals;
		std::vector<FloatVector> FloatVectors;
		std::vector<BoolValue> BoolVals;
		std::vector<BoolVector> BoolVectors;
		std::vector<StringValue> StringVals;
		std::vector<StringVector> StringVectors;
	
		std::vector<Section> ChildSections;
	};
	
	struct Config
	{
		std::vector<Section> RootSections;
	};


	//Helper Function to parse the Configfile
	void DeleteWhitespacesFromLine(std::string &line)
	{
		line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
	}

	void DeleteCharFromLine(std::string &line,char Char)
	{
		line.erase(std::remove(line.begin(), line.end(), Char), line.end());
	}

	void DeleteOpenAndCloseingCurlyBracesFromLine(std::string &line)
	{
		line.erase(0, 1);
		line.erase(line.size() - 1, 1);
	}

	void DeleteOpenAndCloseingQuotationMarkFromLine(std::string &line)
	{
		line.erase(line.begin());
		line.erase(line.size() - 1);
	}

	bool HasOpenAndCloseingCurlyBraces(const std::string &line)
	{
		if (line.find_first_of("{") == 0)
		{
			return (line.find_last_of("}") == line.size() - 1);
		}
		else
		{
			return false;
		}
	}

	bool HasOpenAndCloseingQuotationMarks(const std::string &line)
	{
		if (line.find_first_of("\"") == 0)
		{
			return (line.find_last_of("\"") == line.size() - 1);
		}
		else
		{
			return false;
		}
	}

	bool HasOpenAndCloseingSquareBrackets(const std::string &line)
	{
		if (line.find_first_of("[") == 0)
		{
			return (line.find_last_of("]") == line.size() - 1);
		}
		else
		{
			return false;
		}
	}

	bool IsOnlyWhitespacesLine(const std::string &line)
	{
		return (line.find_first_not_of(" ") == line.npos);
	}

	void RemoveCommentFromLine(std::string &line)
	{
		if (line.find("#") != line.npos)
		{
			line.erase(line.find("#"));
		}
	}


	bool IsSectionNameLine(const std::string &line)
	{
		std::string lineContent = line;
		DeleteWhitespacesFromLine(lineContent);

		if (lineContent.find_first_of("[") == 0)
		{
			if (lineContent.find_first_of("[", lineContent.find_first_of("[") + 1) == std::string::npos)
			{
				if (lineContent.find_first_of("]") == lineContent.size() - 1)
				{
					if (lineContent.find_first_of("]", lineContent.find_first_of("]") + 1) == std::string::npos)
					{
						if (lineContent.find_first_of("=") == std::string::npos)
						{
							return true;
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
		else
		{
			return false;
		}
	}

	bool IsSectionNameInput(const std::string &input)
	{
		std::string lineContent = input;
		DeleteWhitespacesFromLine(lineContent);

		if (lineContent.find_first_of(".") == std::string::npos)
		{
			if (lineContent.find_first_of("=") == std::string::npos)
			{
				return true;
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

	bool IsChildSectionNameLine(const std::string &line)
	{
		std::string lineContent = line;
		DeleteWhitespacesFromLine(lineContent);

		if (lineContent.find_first_of("[") == 0)
		{
			if (lineContent.find_first_of("]") != std::string::npos)
			{
				if (lineContent.find_first_of(".") != std::string::npos)
				{
					if (lineContent.find_first_of("=") == std::string::npos)
					{
						size_t n = std::count(lineContent.begin(), lineContent.end(), '.');

						for (int i = 0; i <= n; i++)
						{
							int PointPos = lineContent.find_first_of(".");
							std::string TempValue = lineContent.substr(0, PointPos);

							if (!HasOpenAndCloseingSquareBrackets(TempValue))
							{
								return false;
							}
							lineContent.erase(0, PointPos + 1);
						}
						return true;
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

	bool IsChildSectionNameInput(const std::string &input)
	{
		std::string lineContent = input;
		DeleteWhitespacesFromLine(lineContent);
		if (lineContent.size() > 0)
		{
			if (lineContent.find_first_of("=") == std::string::npos)
			{
				size_t n = std::count(lineContent.begin(), lineContent.end(), '.');
				for (int i = 0; i <= n; i++)
				{
					int PointPos = lineContent.find_first_of(".");
					std::string TempValue = lineContent.substr(0, PointPos);

					if (IsOnlyWhitespacesLine(TempValue))
					{
						return false;
					}
					lineContent.erase(0, PointPos + 1);
				}
				return true;
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

	bool IsValueLine(const std::string &line)
	{
		if (line.find_first_of("=") != std::string::npos)
		{
			std::string value = line;

			DeleteWhitespacesFromLine(value);

			if (value.find_first_of("=") != 0)
			{		
				int pos = line.find_first_of("=") + 1;

				if (!(pos >= line.size()))
				{
					return (line.find_first_not_of(" ", pos) != std::string::npos);
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
		else
		{
			return false;
		}
	}



	bool IsIntValueLine(const std::string &line)
	{
		int StartPos = line.find_first_of("=") + 1;
		std::string Value = line.substr(StartPos, std::string::npos);
		
		if (Value.find_first_of(".") == std::string::npos)
		{
			DeleteWhitespacesFromLine(Value);
			DeleteCharFromLine(Value, '-');
			return std::all_of(Value.begin(), Value.end(), ::isdigit);
		}
		else
		{
			return false;
		}
	}

	bool IsFloatValueLine(const std::string &line)
	{
		int StartPos = line.find_first_of("=") + 1;
		std::string Value = line.substr(StartPos, std::string::npos);
		

		if (Value.find_first_of(".") != std::string::npos)
		{
			DeleteWhitespacesFromLine(Value);
			DeleteCharFromLine(Value, '.');
			DeleteCharFromLine(Value, '-');

			return std::all_of(Value.begin(), Value.end(), ::isdigit);
		}
		else
		{
			return false;
		}
	}

	bool IsBoolValueLine(const std::string &line)
	{
		int StartPos = line.find_first_of("=") + 1;
		std::string Value = line.substr(StartPos, std::string::npos);
		DeleteWhitespacesFromLine(Value);

		if (Value == "true" || Value == "True" || Value == "1" || Value == "False" || Value == "false" || Value == "0")
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool IsStringValueLine(const std::string &line)
	{
		int ValStartPos = line.find_first_of("=") + 1;
		std::string Value = line.substr(ValStartPos, std::string::npos);
		DeleteWhitespacesFromLine(Value);

		return HasOpenAndCloseingQuotationMarks(Value);
	}



	bool IsIntVectorLine(const std::string &line)
	{
		int StartPos = line.find_first_of("=") + 1;
		std::string Value = line.substr(StartPos, std::string::npos);

		if (Value.find_first_of(".") == std::string::npos)
		{
			DeleteWhitespacesFromLine(Value);
			if (HasOpenAndCloseingCurlyBraces(Value))
			{
				
				DeleteOpenAndCloseingCurlyBracesFromLine(Value);
				DeleteCharFromLine(Value, ',');
				DeleteCharFromLine(Value, '-');

				return std::all_of(Value.begin(), Value.end(), ::isdigit);
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

	bool IsFloatVectorLine(const std::string &line)
	{
		int StartPos = line.find_first_of("=") + 1;
		std::string Value = line.substr(StartPos, std::string::npos);
		DeleteWhitespacesFromLine(Value);

		if (HasOpenAndCloseingCurlyBraces(Value))
		{
			if (Value.find_first_of(".") != std::string::npos)
			{
				DeleteOpenAndCloseingCurlyBracesFromLine(Value);
				DeleteCharFromLine(Value, ',');
				DeleteCharFromLine(Value, '.');
				DeleteCharFromLine(Value, '-');
				DeleteCharFromLine(Value, 'e');
				DeleteCharFromLine(Value, 'E');
				return std::all_of(Value.begin(), Value.end(), ::isdigit);

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

	bool IsBoolVectorLine(const std::string &line)
	{
		int StartPos = line.find_first_of("=") + 1;
		std::string Value = line.substr(StartPos, std::string::npos);
		DeleteWhitespacesFromLine(Value);

		if (HasOpenAndCloseingCurlyBraces(Value))
		{
			DeleteOpenAndCloseingCurlyBracesFromLine(Value);

			size_t n = std::count(Value.begin(), Value.end(), ',');

			for (int i = 0; i <= n; i++)
			{
				int CommaPos = Value.find_first_of(",");
				std::string TempValue = Value.substr(0, CommaPos);

				if ((TempValue != "True" && TempValue != "true" && TempValue != "1" && TempValue != "False" && TempValue != "false" && TempValue != "0"))
				{
					return false;
				}
				Value.erase(0, CommaPos + 1);
			}

			return true;
		}
		else
		{
			return false;
		}
	}

	bool IsStringVectorLine(const std::string &line)
	{
		int StartPos = line.find_first_of("=") + 1;
		std::string Value = line.substr(StartPos, std::string::npos);
		DeleteWhitespacesFromLine(Value);

		if (HasOpenAndCloseingCurlyBraces(Value))
		{
			DeleteOpenAndCloseingCurlyBracesFromLine(Value);

			size_t n = std::count(Value.begin(), Value.end(), ',');

			for (int i = 0; i <= n; i++)
			{
				int CommaPos = Value.find_first_of(",");
				std::string TempValue = Value.substr(0, CommaPos);

				if (!HasOpenAndCloseingQuotationMarks(TempValue))
				{
					return false;
				}
				Value.erase(0, CommaPos + 1);
			}
			return true;
		}
		else
		{
			return false;
		}
	}

	bool IsNumericValue(const std::string &str)
	{
		if (str.find_first_of(".") != std::string::npos)
		{
			std::string Temp1 = str.substr(0, str.find_first_of(".") - 1);
			std::string Temp2 = str.substr(str.find_first_of(".") + 1, std::string::npos);

			bool res = std::all_of(Temp1.begin(), Temp1.end(), ::isdigit);
			if (!res)
			{
				return false;
			}

			return std::all_of(Temp2.begin(), Temp2.end(), ::isdigit);
		}

		return std::all_of(str.begin(), str.end(), ::isdigit);
	}



	std::string GetSectionNameFromLine(const std::string &line)
	{
		int StartPos = line.find_first_of("[") + 1;
		int Length = line.find_first_of("]") - StartPos;
		std::string SectionName = line.substr(StartPos, Length);
		DeleteWhitespacesFromLine(SectionName);

		return SectionName;
	}

	std::vector<std::string> GetChildSectionNameListFromLine(const std::string &line)
	{

		std::vector<std::string> TempSectionNameVector;
		std::string TempLine = line;
		size_t n = std::count(TempLine.begin(), TempLine.end(), '.');

		for (int i = 0; i <= n; i++)
		{
			int CommaPos = TempLine.find_first_of(".");
			std::string TempValue = TempLine.substr(0, CommaPos);

			unsigned first = TempValue.find_first_of("[") + 1;
			unsigned last = TempValue.find_last_of("]");

			TempValue = TempValue.substr(first, last - first);

			TempSectionNameVector.push_back(TempValue);

			TempLine.erase(0, CommaPos + 1);
		}

		return TempSectionNameVector;
	}

	std::vector<std::string> GetSectionNameListFromFunctionArg(const std::string &funcarg)
	{

		std::vector<std::string> TempSectionNameVector;
		std::string TempLine = funcarg;
		size_t count = std::count(TempLine.begin(), TempLine.end(), '.');

		for (int i = 0; i <= count; i++)
		{
			int PointPos = TempLine.find_first_of(".");
			std::string TempValue = TempLine.substr(0, PointPos);

			TempSectionNameVector.push_back(TempValue);

			TempLine.erase(0, PointPos + 1);
		}

		return TempSectionNameVector;
	}

	std::string GetValueNameFromLine(const std::string &line)
	{
		int length = line.find_first_of("=");
		std::string ValueName = line.substr(0, length);

		DeleteWhitespacesFromLine(ValueName);

		return ValueName;
	}



	int GetIntValueFromLine(const std::string &line)
	{
		int StartPos = line.find_first_of("=") + 1;
		std::string Value = line.substr(StartPos, std::string::npos);
		DeleteWhitespacesFromLine(Value);

		return std::stoi(Value);
	}

	float GetFloatValueFromLine(const std::string &line)
	{
		int StartPos = line.find_first_of("=") + 1;
		std::string Value = line.substr(StartPos, std::string::npos);
		DeleteWhitespacesFromLine(Value);

		return std::stof(Value);
	}

	bool GetBoolValueFromLine(const std::string &line)
	{
		int StartPos = line.find_first_of("=") + 1;
		std::string Value = line.substr(StartPos, std::string::npos);
		DeleteWhitespacesFromLine(Value);

		if (Value == "true")
		{
			return true;
		}
		if (Value == "True")
		{
			return true;
		}
		if (Value == "1")
		{
			return true;
		}
		if (Value == "false")
		{
			return false;
		}
		if (Value == "False")
		{
			return false;
		}
		if (Value == "0")
		{
			return false;
		}

		return false;
	}

	std::string GetStringValueFromLine(const std::string &line)
	{
		int StartPos = line.find_first_of("=") + 1;
		std::string Value = line.substr(StartPos, std::string::npos);

		unsigned first = line.find_first_of("\"") + 1;
		unsigned last = line.find_last_of("\"");

		Value = line.substr(first, last - first);

		//DeleteOpenAndCloseingQuotationMarkFromLine(Value);

		return Value;
	}

	std::vector<int> GetIntVectorFromLine(const std::string &line)
	{
		std::vector<int> TempVector;
		int StartPos = line.find_first_of("=") + 1;
		std::string Value = line.substr(StartPos, std::string::npos);
		DeleteWhitespacesFromLine(Value);
		DeleteOpenAndCloseingCurlyBracesFromLine(Value);

		std::stringstream ss(Value);

		int i;

		while (ss >> i)
		{
			TempVector.push_back(i);
			if (ss.peek() == ',')
				ss.ignore();
		}

		return TempVector;
	}

	std::vector<float> GetFloatVectorFromLine(const std::string &line)
	{
		std::vector<float> TempVector;
		int StartPos = line.find_first_of("=") + 1;
		std::string Value = line.substr(StartPos, std::string::npos);
		DeleteWhitespacesFromLine(Value);
		DeleteOpenAndCloseingCurlyBracesFromLine(Value);

		std::stringstream ss(Value);

		float i;

		while (ss >> i)
		{
			TempVector.push_back(i);
			if (ss.peek() == ',')
				ss.ignore();
		}

		return TempVector;
	}

	std::vector<bool> GetBoolVectorFromLine(const std::string &line)
	{
		std::vector<bool> TempVector;
		int StartPos = line.find_first_of("=") + 1;
		std::string Value = line.substr(StartPos, std::string::npos);
		DeleteWhitespacesFromLine(Value);
		DeleteOpenAndCloseingCurlyBracesFromLine(Value);

		size_t n = std::count(Value.begin(), Value.end(), ',');

		for (int i = 0; i <= n; i++)
		{
			int CommaPos = Value.find_first_of(",");
			std::string TempValue = Value.substr(0, CommaPos);

			if (TempValue == "true")
			{
				TempVector.push_back(true);
			}
			if (TempValue == "True")
			{
				TempVector.push_back(true);
			}
			if (TempValue == "1")
			{
				TempVector.push_back(true);
			}
			if (TempValue == "false")
			{
				TempVector.push_back(false);
			}
			if (TempValue == "False")
			{
				TempVector.push_back(false);
			}
			if (TempValue == "0")
			{
				TempVector.push_back(false);
			}

			Value.erase(0, CommaPos + 1);
		}

		return TempVector;
	}

	std::vector<std::string> GetStringVectorFromLine(const std::string &line)
	{
		std::vector<std::string> TempVector;
		int StartPos = line.find_first_of("=") + 1;
		std::string Value = line.substr(StartPos, std::string::npos);
		DeleteOpenAndCloseingCurlyBracesFromLine(Value);

		size_t n = std::count(Value.begin(), Value.end(), ',');

		for (int i = 0; i <= n; i++)
		{
			int CommaPos = Value.find_first_of(",");
			std::string TempValue = Value.substr(0, CommaPos);

			unsigned first = TempValue.find_first_of("\"") + 1;
			unsigned last = TempValue.find_last_of("\"");

			TempValue = TempValue.substr(first, last - first);

			TempVector.push_back(TempValue);

			Value.erase(0, CommaPos + 1);
		}

		return TempVector;
	}

public:

	ConfigDataClass();
	ConfigDataClass(const ConfigDataClass&);
	~ConfigDataClass();

	bool LoadConfigDataFile(const std::string FileName);
	void SaveConfigDataFile(const std::string FileName, const std::string CommentAtStartOfFile);
	
	void ClearConfigData();

	//Add Value Functions
	bool AddIntValueByName(const std::string SectionName, const std::string ValueName, int Value);
	bool AddFloatValueByName(const std::string SectionName, const std::string ValueName, float Value);
	bool AddBoolValueByName(const std::string SectionName, const std::string ValueName, bool Value);
	bool AddStringValueByName(const std::string SectionName, const std::string ValueName, std::string Value);

	//Add Vector Functions
	bool AddIntVectorByName(const std::string SectionName, const std::string ValueName, std::vector<int> Value);
	bool AddFloatVectorByName(const std::string SectionName, const std::string ValueName, std::vector<float> Value);
	bool AddBoolVectorByName(const std::string SectionName, const std::string ValueName, std::vector<bool> Value);
	bool AddStringVectorByName(const std::string SectionName, const std::string ValueName, std::vector<std::string> Value);

	//Get Section info's
	int GetNumberOfRootSections();
	std::vector<int> GetIndiciePathToRootSecton(int RootSectionIndex);
	int GetNumberOfAllChildSectionsFromRoot(const int RootSectionIndex);
	std::vector<int> GetIndiciePathToChildFromRoot(const int RootSectionIndex, const int ChildIndex);

	bool GetSectionName(const std::vector<int> Indicies, std::string& SectionName);

	//Get count of section values
	int GetNumberOfIntValues(std::vector<int>& Indicies);
	int GetNumberOfIntVectors(std::vector<int>& Indicies);
	int GetNumberOfFloatValues(std::vector<int>& Indicies);
	int GetNumberOfFloatVectors(std::vector<int>& Indicies);
	int GetNumberOfBoolValues(std::vector<int>& Indicies);
	int GetNumberOfBoolVectors(std::vector<int>& Indicies);
	int GetNumberOfStringValues(std::vector<int>& Indicies);
	int GetNumberOfStringVectors(std::vector<int>& Indicies);
	
	//Get section values
	bool GetIntValueNameByIndex(const std::vector<int>& Indicies, const int ValueIndex, std::string& ValueName);
	bool GetIntValueByIndex(const std::vector<int>& Indicies, const int ValueIndex, int& Value);
	bool GetIntValueByName(const std::string SectionName, const std::string ValueName, int& Value);

	bool GetFloatValueNameByIndex(const std::vector<int>& Indicies, const int ValueIndex, std::string& ValueName);
	bool GetFloatValueByIndex(const std::vector<int>& Indicies, const int ValueIndex, float& Value);
	bool GetFloatValueByName(const std::string SectionName, const std::string ValueName, float& Value);

	bool GetBoolValueNameByIndex(const std::vector<int>& Indicies, const int ValueIndex, std::string& ValueName);
	bool GetBoolValueByIndex(const std::vector<int>& Indicies, const int ValueIndex, bool& Value);
	bool GetBoolValueByName(const std::string SectionName, const std::string ValueName, bool& Value);

	bool GetStringValueNameByIndex(const std::vector<int>& Indicies, const int ValueIndex, std::string& ValueName);
	bool GetStringValueByIndex(const std::vector<int>& Indicies, const int ValueIndex, std::string& Value);
	bool GetStringValueByName(const std::string SectionName, const std::string ValueName, std::string& Value);


	//Get section vectors
	bool GetIntVectorNameByIndex(const std::vector<int>& Indicies, const int ValueIndex, std::string &ValueName);
	bool GetIntVectorByIndex(const std::vector<int>& Indicies, const int ValueIndex, std::vector<int> &Value);
	bool GetIntVectorByName(const std::string SectionName, const std::string ValueName, std::vector<int> &Value);

	bool GetFloatVectorNameByIndex(const std::vector<int>& Indicies, const int ValueIndex, std::string &ValueName);
	bool GetFloatVectorByIndex(const std::vector<int>& Indicies, const int ValueIndex, std::vector<float> &Value);
	bool GetFloatVectorByName(const std::string SectionName, const std::string ValueName, std::vector<float> &Value);

	bool GetBoolVectorNameByIndex(const std::vector<int>& Indicies, const int ValueIndex, std::string& ValueName);
	bool GetBoolVectorByIndex(const std::vector<int>& Indicies, const int ValueIndex, std::vector<bool> &Value);
	bool GetBoolVectorByName(const std::string SectionName, const std::string ValueName, std::vector<bool> &Value);

	bool GetStringVectorNameByIndex(const std::vector<int>& Indicies, const int ValueIndex, std::string& ValueName);
	bool GetStringVectorByIndex(const std::vector<int>& Indicies, const int ValueIndex, std::vector<std::string> &Value);
	bool GetStringVectorByName(const std::string SectionName, const std::string ValueName, std::vector<std::string> &Value);

private:

	// Add section by section path list to the tree.
	bool AddSection(std::vector<std::string> SectionPathList, Section*& AddedSection);

	bool GetRootSectionByName(std::string SectionName, Section*& RootSection);
	bool GetRootSectionIndex(std::string SectionName, int& RootSectionIndex);

	bool GetChildSectionFromParent(Section* ParentSection, std::string SectionName, Section*& ChildSection);
	bool GetChildBySectionPath(std::vector<std::string> SectionPath, Section*& ChildSection);

	void GetChildSectionIndicieVector(Section* RootSection, const int ChildIndex, std::vector<int>& Indicies, int& ChildCount);
	void GetChildByIndex(Section* RootSection, int Index, Section*& ChildSection);
	bool GetChildByIndicieVector(const std::vector<int>& Indicies, Section*& ChildSection);

	bool CheckIfRootSectionExist(std::string SectionName);
	bool CheckIfChildSectionExist(Section* ParentSection, std::string SectionName);
	bool CheckIfSectionPathExist(std::vector<std::string> SectionPath);

	void CalculateNumberOfAllChildsFromRoot(Section* RootSection, int& NumberOfChildSections);
	void PrintSectionToFile(Section* SectionData, std::ofstream& OutputFile);

	Config ConfigData;
};

#endif