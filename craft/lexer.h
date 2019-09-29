#ifndef __LEXER_H
#define __LEXER_H

/**
 * ����
 * token�ĳ��Ȳ��ܳ���63
 * ���ʷ��������ı����Ȳ��ܳ���uint64_t���͵���󳤶�
 * ���ʷ��������ı��е�token�������ܳ���uint32_t���͵���󳤶�
 */

/**
 * �ʷ������������ʽ
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
