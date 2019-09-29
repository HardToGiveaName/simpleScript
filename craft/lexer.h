#ifndef __LEXER_H
#define __LEXER_H

/**
 * 限制
 * token的长度不能超过63
 * 做词法解析的文本长度不能超过uint64_t类型的最大长度
 * 做词法解析的文本中的token数量不能超过uint32_t类型的最大长度
 */

/**
 * 词法规则的正则表达式
 * Identifier: [a-zA-Z_] ([a-zA-Z_] | [0-9])*
 * IntLiteral: [0-9]+
 * Int :       'int'
 * Assignment: '='
 * GT :        '>'
 * GE :        '>='
 * Plus:       '+'
 * Minus:      '-'
 * Star:       '*'
 * Slash:      '/'
 * Semicolon:  ';'
 * LeftParen:  '('
 * RightParen: ')'
 */

#include "token.h"


Tokens lexer(char *str);

#endif
