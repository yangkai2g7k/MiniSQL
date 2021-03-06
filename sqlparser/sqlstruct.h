#ifndef SQLSTRUCT_H
#define SQLSTRUCT_H
#include "sqlparser.hh"
#include <vector>
//typedef yy::sqlparser::token::tokentype TOKEN;
namespace sqlstruct{
	struct col_attr{
		int type;
		std::string value;
	};
	struct record_t{
		std::string name;
		std::vector<col_attr>  attr;
		int  data_type;
	};
	
	struct create_col_list{
		std::vector<std::string> primarykey;
		std::vector<std::string> indexkey;
		std::vector<record_t> record;
	};
	struct createtable{
		std::string name;
		struct create_col_list col;
		//std::vector<struct record_t> record;
		//vector<std::string> primarykey;
		//vector<std::string> indexkey;
	};
	struct dropindex{
		std::string tablename;
		std::string indexname;
		std::vector<std::string> col;
	};
	struct insertitem{
		std::string value;
		int data_type;
	};
	struct insertvalues{
		std::string tablename;
		std::vector<insertitem> item;
	};
	struct astree{
		std::string value;
		bool isleaf;
		int operate;
		struct astree *left,*right;
	};
	struct selecttable{
		std::string fromtable;
		std::vector<std::string> col;
		bool selectall;
		struct astree *where;
	};
	struct deletetable{
		std::string fromtable;
		struct astree *where;
		bool deleteall;
	};
	struct createindex{
		std::string indexname;
		std::string tablename;
		std::vector<std::string> col;
	};
	enum attr_type{
		AUTO_INCREMENT,
		DEFAULT,
		NULLX,
		PRIMARY,
		UNIQUE,
		INTNUM,
		STRING,
		FLOATNUM
	};
	enum operate {
		AND,
		OR,
		NOT,
		ISNULL,
		LESS,
		LESSOREQUAL,
		EQUAL,
		GREATOREQUAL,
		GREAT,
		NOTEQUAL
	};
}
#endif
