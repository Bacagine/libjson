/**
 * json.h
 *
 * Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
 *
 * Description: Manipulate JSON in C language
 *
 * Date: 2024-02-24
 */

#ifndef _JSON_H_
#define _JSON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// JSON return values
#define JSON_ERROR 0
#define JSON_OK    1

// JSON data types
#define JSONTYPE_INT    0
#define JSONTYPE_STR    1
#define JSONTYPE_BOOL   2
#define JSONTYPE_OBJ    3
#define JSONTYPE_ARRAY  4
#define JSONTYPE_NULL   5

/**
 * This structure that represents a JSON file line
 */
typedef struct STRUCT_JSON
{
  char *pszKey;
  int iKeyType;
  int iDataSize;
  void *pData;
} STRUCT_JSON, *PSTRUCT_JSON;

/**
 * Read a json from a file and save the content in a string
 *
 * How to use:
 *
 * char *pszJSON = NULL;
 * PSTRUCT_JSON pstTmpJSON = astJsonPerson;
 *
 * if(!iJSON_Read(&pszJSON, "person.json"))
 * {
 *   fprintf(stderr, "E: Impossivel ler o arquivo person.json");
 *
 *   if(pszJSON)
 *   {
 *     free(pszJSON);
 *     pszJSON = NULL;
 *   }
 *
 *   return JSON_ERROR;
 * }
 *
 *  printf("JSON lido:\n");
 *  printf("pszJSON [%s]\n", pszJSON);
 *
 *  free(pszJSON);
 *  pszJSON = NULL;
 */
int iJSON_Read(char **ppszJSON, const char *kpszFileName);

/**
 * Preenche uma STRUCT_JSON com o conteudo de paszJSON
 *
 * How to use:
 *
 * char *pszJSON = NULL;
 * PSTRUCT_JSON pstTmpJSON = astJsonPerson;
 *
 * if(!iJSON_LoadKeys(pszJSON, &pstTmpJSON))
 * {
 *   fprintf(stderr, "E: Erro ao carregar JSON!");
 *
 *   free(pszJSON);
 *   pszJSON = NULL;
 *
 *   return JSON_ERROR;
 * }
 */
int iJSON_LoadKeys(const char *kpszJSON, PSTRUCT_JSON *pastJSON);

/**
 * Escreve o conteudo da STRUCT_JSON em um arquivo
 *
 * How to use:
 *
 * FILE *fpJSON = NULL;
 * PSTRUCT_JSON pstTmpJSON = astJsonPerson;
 *
 * if((fpJSON = fopen("person.json")) == NULL)
 * {
 *   fprintf(stderr, "E: impossivel criar o arquivo person.json!\n");
 *
 *   return JSON_ERROR;
 * }
 *
 * if(!iJSON_WriteFile(fpJSON, pstPersonJson)
 * {
 *   fprintf(stderr, "E: Impossivel criar o conteudo do arquivo person.json!\n");
 *
 *   fclose(fpJSON);
 *   fpJSON = NULL;
 *
 *   return JSON_ERROR;
 * }
 *
 * fclose(fpJSON);
 * fpJSON = NULL;
 *
 * printf("\nDados coletados do JSON:\n");
 * printf
 * (
 *   "{\n"
 *   "  \"nome\": \"%s\",\n"
 *   "  \"age\": %d,\n"
 *   "  \"phone\": \"%s\",\n"
 *   "  \"email\": \"%s\",\n"
 *   "  \"CPF\": \"%s\",\n"
 *   "  \"nationality\": \"%s\"\n"
 *   "}\n", gstPerson.stPersonInfo.szName,
 *        gstPerson.iAge,
 *        gstPerson.stPersonInfo.szPhone,
 *        gstPerson.stPersonInfo.szEmail,
 *        gstPerson.szCPF,
 *        gstPerson.szNationality
 * );
 *
 * free(pszJSON);
 * pszJSON = NULL;
 */
int iJSON_WriteFile(FILE *fpJSON, PSTRUCT_JSON astJSON);

/**
 * Escreve o conteudo da STRUCT_JSON em uma string
 *
 * How to use:
 *
 * char *pszJSON = NULL
 * PSTRUCT_JSON pstTmpJSON = astJsonPerson;
 *
 * if(!iJSON_DumpJSON(&pszJSON, pstTmpJSON))
 * {
 *   return JSON_ERROR;
 * }
 *
 * printf("CONTEUDO DA STRING JSON [%s]\n", pszJSON);
 *
 * free(pszJSON);
 * pszJSON = NULL;
 */
int iJSON_DumpJSON(char **ppaszJSON, PSTRUCT_JSON astJSON);

#endif /* _JSON_H_ */
