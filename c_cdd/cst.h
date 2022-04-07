#ifndef C_CDD_CST_H
#define C_CDD_CST_H

#ifdef __cplusplus
#include <cstdbool>
#include <cstdlib>
#include <cstring>
extern "C" {
#else
#include <stdlib.h>
#include <string.h>

#if __STDC_VERSION__ >= 199901L
#include <stdbool.h>
#else
#include <c_cdd_stdbool.h>
#endif /* __STDC_VERSION__ >= 199901L */

#endif /* __cplusplus */

#include <c_cdd_export.h>

struct str_elem {
  const char *s;
  size_t n;
  struct str_elem *next;
};

struct CstNode;

#define CST_WITH_BODY

#define CstNode_base_properties                                                \
  size_t pos_start; /* where in full-source `value` starts */                  \
  struct CstNode *scope;                                                       \
  const char *value

/* two phase parser */
extern C_CDD_EXPORT const struct str_elem *scanner(const char *);
extern C_CDD_EXPORT const struct CstNode **parser(struct str_elem *);

struct BlockStart {
  CstNode_base_properties;
};

struct BlockEnd {
  CstNode_base_properties;
};

/* mostly from reviewing http://www.quut.com/c/ANSI-C-grammar-y.html */

struct CppComment {
  CstNode_base_properties;
};

struct CComment {
  CstNode_base_properties;
};

enum Keywords {
  AUTO,
  BREAK,
  CASE,
  CHAR,
  CONST,
  CONTINUE,
  DEFAULT,
  DO,
  DOUBLE,
  ELSE,
  ENUM,
  EXTERN,
  FLOAT,
  FOR,
  GOTO,
  IF,
  INLINE,
  INT,
  LONG,
  REGISTER,
  RESTRICT,
  RETURN,
  SHORT,
  SIGNED,
  SIZEOF,
  STATIC,
  STRUCT,
  SWITCH,
  TYPEDEF,
  UNION,
  UNSIGNED,
  VOID,
  VOLATILE,
  WHILE,
  ALIGNAS,
  ALIGNOF,
  ATOMIC,
  BOOL,
  COMPLEX,
  GENERIC,
  IMAGINARY,
  NORETURN,
  STATIC_ASSERT,
  THREAD_LOCAL,
  FUNC_NAME
};

/*
static const std::unordered_map<std::string, enum Keywords> keyword2enum {
  {"auto", AUTO},
  {"break", BREAK},
  {"case", CASE},
  {"char", CHAR},
  {"const", CONST},
  {"continue", CONTINUE},
  {"default", DEFAULT},
  {"do", DO},
  {"double", DOUBLE},
  {"else", ELSE},
  {"enum", ENUM},
  {"extern", EXTERN},
  {"float", FLOAT},
  {"for", FOR},
  {"goto", GOTO},
  {"if", IF},
  {"inline", INLINE},
  {"int", INT},
  {"long", LONG},
  {"register", REGISTER},
  {"restrict", RESTRICT},
  {"return", RETURN},
  {"short", SHORT},
  {"signed", SIGNED},
  {"sizeof", SIZEOF},
  {"static", STATIC},
  {"struct", STRUCT},
  {"switch", SWITCH},
  {"typedef", TYPEDEF},
  {"union", UNION},
  {"unsigned", UNSIGNED},
  {"void", VOID},
  {"volatile", VOLATILE},
  {"while", WHILE},
  {"_Alignas", ALIGNAS},
  {"_Alignof", ALIGNOF},
  {"_Atomic", ATOMIC},
  {"_Bool", BOOL},
  {"_Complex", COMPLEX},
  {"_Generic", GENERIC},
  {"_Imaginary", IMAGINARY},
  {"_Noreturn", NORETURN},
  {"_Static_assert", STATIC_ASSERT},
  {"_Thread_local", THREAD_LOCAL},
  {"__func__", FUNC_NAME}
};
*/

// enum StorageClassSpecifier {
//   TYPEDEF, /* identifiers must be flagged as TYPEDEF_NAME */
//   EXTERN,
//   STATIC,
//   THREAD_LOCAL,
//   AUTO,
//   REGISTER
// };
//
// enum TypeSpecifier {
//   VOID,
//   CHAR,
//   SHORT,
//   INT,
//   LONG,
//   FLOAT,
//   DOUBLE,
//   SIGNED,
//   UNSIGNED,
//   BOOL,
//   COMPLEX,
//   IMAGINARY        /* non-mandated extension */
//   ,
//   /*atomic_type_specifier,
//   struct_or_union_specifier,
//   enum_specifier,
//   TYPEDEF_NAME   */     /* after it has been defined as such */
// };

struct Expression {
  CstNode_base_properties;
}; /* fallback if nothing else matches */

struct Label {
  CstNode_base_properties;
  const char *label;
};

struct Case {
  CstNode_base_properties;
  const char *val;
};

struct Switch {
  CstNode_base_properties;
  const char *condition;
#ifdef CST_WITH_BODY
  struct CstNode *body;
#endif /* CST_WITH_BODY */
};

struct If {
  CstNode_base_properties;
  const char *condition;
#ifdef CST_WITH_BODY
  struct CstNode *body;
#endif /* CST_WITH_BODY */
};

struct Else {
  CstNode_base_properties;
#ifdef CST_WITH_BODY
  struct CstNode *body;
#endif /* CST_WITH_BODY */
};

struct ElseIf {
  CstNode_base_properties;
  const char *condition;
#ifdef CST_WITH_BODY
  struct CstNode *body;
#endif /* CST_WITH_BODY */
};

struct While {
  CstNode_base_properties;
  const char *condition;
#ifdef CST_WITH_BODY
  struct CstNode *body;
#endif /* CST_WITH_BODY */
};

struct Do {
  CstNode_base_properties;
#ifdef CST_WITH_BODY
  struct CstNode *body;
#endif /* CST_WITH_BODY */
};

// struct DoWhile { CstNode_base_properties; };

struct For {
  CstNode_base_properties;
  const char *decl_or_expr0, *decl_or_expr1, *expr;
#ifdef CST_WITH_BODY
  struct CstNode *body;
#endif /* CST_WITH_BODY */
};

struct GoTo {
  CstNode_base_properties;
  const char *label;
};

struct Continue {
  CstNode_base_properties;
};

struct Break {
  CstNode_base_properties;
};

struct Return {
  CstNode_base_properties;
  const char *val;
};

#define Declaration_properties                                                 \
  enum Keywords *specifiers;                                                   \
  const char *type; /* set to NULL if `specifiers` has the right type [i.e.,   \
                       builtin type] */                                        \
  const char *name

struct Declaration {
  CstNode_base_properties;
  Declaration_properties;
};

struct Definition {
  CstNode_base_properties;
  Declaration_properties;
  const char *value_assigned;
};

struct Struct {
  CstNode_base_properties;
  const char *name;
  struct Declaration **fields;
  const char **declaration_list;
};

struct Union {
  CstNode_base_properties;
  const char *name;
  struct Declaration **fields;
  const char **declaration_list;
};

struct Enum {
  CstNode_base_properties;
  const char *name;
  struct Declaration **fields;
  const char **enumerator_list;
};

struct FunctionPrototype {
  CstNode_base_properties;
  const char *name;
  struct Declaration **args;
};

struct FunctionStart {
  CstNode_base_properties;
};

struct Function {
  CstNode_base_properties;
  enum Keywords *specifiers;
  const char *type; /* set to NULL if `specifiers` has the right type [i.e.,
                       builtin type] */
  const char *name;
  struct Declaration *args;
#ifdef CST_WITH_BODY
  struct CstNode *body;
#endif /* CST_WITH_BODY */
};

struct MacroIf {
  CstNode_base_properties;
  const char *expr;
#ifdef CST_WITH_BODY
  struct CstNode *body;
#endif /* CST_WITH_BODY */
};

struct MacroElif {
  CstNode_base_properties;
  const char *expr;
#ifdef CST_WITH_BODY
  struct CstNode *body;
#endif /* CST_WITH_BODY */
};

struct MacroElse {
  CstNode_base_properties;
  const char *expr;
#ifdef CST_WITH_BODY
  struct CstNode *body;
#endif /* CST_WITH_BODY */
};

struct MacroIfDef {
  CstNode_base_properties;
  const char *expr;
#ifdef CST_WITH_BODY
  struct CstNode *body;
#endif /* CST_WITH_BODY */
};

struct MacroDefine {
  CstNode_base_properties;
  const char *expr;
};

struct MacroInclude {
  CstNode_base_properties;
  const char *val;
};

struct MacroPragma {
  CstNode_base_properties;
  const char *val;
};

enum CstNodeKind {
  Expression,
  BlockStart,
  BlockEnd,

  Label,
  Case,
  Switch,
  If,
  Else,
  ElseIf,
  While,
  Do,
  For,
  GoTo,
  Continue,
  Break,
  Return,
  Declaration,
  Definition,
  Struct,
  Union,
  Enum,
  FunctionPrototype,
  Function,

  MacroIf,
  MacroElif,
  MacroIfDef,
  MacroElse,
  MacroDefine,
  MacroInclude,
  MacroPragma
};

union CstNodeType {
  struct Expression expression;
  struct BlockStart block_start;
  struct BlockEnd block_end;

  struct Label label;
  struct Case _case;
  struct Switch _switch;
  struct If _if;
  struct Else _else;
  struct ElseIf elseif;
  struct While _while;
  struct Do _do;
  struct For _for;
  struct GoTo _goto;
  struct Continue _continue;
  struct Break _break;
  struct Return _return;
  struct Declaration declaration;
  struct Definition definition;
  struct Struct _struct;
  struct Union _union;
  struct Enum _enum;
  struct FunctionPrototype function_prototype;
  struct Function function;

  struct MacroIf macro_if;
  struct MacroElif macro_elif;
  struct MacroIfDef macro_if_def;
  struct MacroElse macro_else;
  struct MacroDefine macro_define;
  struct MacroInclude macro_include;
  struct MacroPragma macro_pragma;
};

struct CstNode {
  enum CstNodeKind kind;
  union CstNodeType type;
};

#ifdef __cplusplus
}
#endif

#endif /* !C_CDD_CST_H */
