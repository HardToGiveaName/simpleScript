#ifndef __PARSER_H
#define __PARSER_H

/**
 * һ���򵥵��﷨��������
 * �ܹ������򵥵ı��ʽ�����������ͳ�ʼ����䡢��ֵ��䡣
 * ��֧�ֵ��﷨����Ϊ��
 *
 * programm -> intDeclare | expressionStatement | assignmentStatement
 * intDeclare -> 'int' Id ( = additive) ';'
 * expressionStatement -> addtive ';'
 * addtive -> multiplicative ( (+ | -) multiplicative)*
 * multiplicative -> primary ( (* | /) primary)*
 * primary -> IntLiteral | Id | (additive)
 */

#include "ast.h"


AST parser(char *str);

#endif
