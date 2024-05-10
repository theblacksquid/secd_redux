
#ifndef SECD_CELL
#define SECD_CELL

typedef enum SECD_Cell_Type SECD_Cell_Type;
typedef enum SECD_Instruction SECD_Instruction;
typedef union Cell_Data Cell_Data;
typedef struct SECD_Pair SECD_Pair;
typedef struct SECD_Cell SECD_Cell;
typedef struct SECD_Array SECD_Array;

struct SECD_Cell
{
    enum SECD_Cell_Type
    {
	SECD_UInt,
	SECD_SInt,
	SECD_Floa,
	SECD_Char,
	SECD_List,
	SECD_Arra,
	SECD_Inst
    } type;
    
    union Cell_Data
    {
	unsigned int  unsigned_int;
	int           signed_int;
	float         float_value;
	unsigned char character;
	SECD_Pair*    pair_value;
	SECD_Array*   array_value;
	enum SECD_Instruction
	{
	    NIL,
	    LDC,
	    LDV,
	    LDF,
	    SEL,
	    JON,
	    APP,
	    RET,
	    DUM,
	    RAP,
	    RTN,
	    CAR,
	    CDR,
	    ATM,
	    CON,
	    EQL,
	    LEQ,
	    ADD,
	    SUB,
	    MUL,
	    DIV,
	    REM,
	    STP,
	} instruction;
    } data;
};

#endif
