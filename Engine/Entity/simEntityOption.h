/*============================================================================
 * @author     : Jae Yong Lee (leejaeyong7@gmail.com)
 * @file       : simEntityOption.h
 * @brief      : Declaration file for Entity Option types
 * Copyright (c) Jae Yong Lee / UIUC Spring 2016
 =============================================================================*/
#ifndef _SIM_ENTITY_OPTION_H_
#define _SIM_ENTITY_OPTION_H_
//----------------------------------------------------------------------------//
//                                  INCLUDES                                  //
//----------------------------------------------------------------------------//
#include <string>
//----------------------------------------------------------------------------//
//                                END INCLUDES                                //
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//                            TYPEDEF DEFINITIONS                             //
//----------------------------------------------------------------------------//
typedef enum optionType{
    STRING,
    DOUBLE,
    INTEGER,
} OptionType;
//----------------------------------------------------------------------------//
//                          END TYPEDEF DEFINITIONS                           //
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//                             CLASS DEFINITIONS                              //
//----------------------------------------------------------------------------//
class AdvancedOption{
public:
    AdvancedOption(std::string _label, OptionType _type){
        label = _label;
        type = _type;
    };
    std::string label;
    OptionType type;
};


class AdvancedOption_Int: public AdvancedOption{
public:
    AdvancedOption_Int(std::string _label, OptionType _type,int _value):
        AdvancedOption(_label,_type){
        value = _value;
    }
    int value;

};

class AdvancedOption_Double: public AdvancedOption{
public:
    AdvancedOption_Double(std::string _label, OptionType _type,double _value):
        AdvancedOption(_label,_type){
        value = _value;
    }
    double value;

};

class AdvancedOption_String: public AdvancedOption{
public:
    AdvancedOption_String(
        std::string _label, OptionType _type,std::string _value
        ):
        AdvancedOption(_label,_type){
        value = _value;
    }
    std::string value;
};
//----------------------------------------------------------------------------//
//                           END CLASS DEFINITIONS                            //
//----------------------------------------------------------------------------//
#endif
