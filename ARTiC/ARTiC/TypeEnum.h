#ifndef TYPE_ENUM_H_INCLUDED
#define TYPE_ENUM_H_INCLUDED

//Enum for types used in this program untill a better method is found.
//ONLY INSERT TYPES TO THE END OF THIS
//It shouldn't matter but some people may be relying on the number value of these enums
static enum TypeEnum {
  FuncDecl_Type,
  VarDecl_Type,
  MemberVarDecl_Type,

  FuncCall_Type,

  ReturnStm_Type,

  //Source_code it's not a type, but this is needed to be here to be able to map likewise the function asking for the code
  Source_Code
  
};
#endif