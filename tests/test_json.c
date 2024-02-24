/**
 * test_json.c
 *
 * Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
 *
 * Description: A simple test about how to use the libjson
 *
 * Date: 2024-02-24
 */

#include "json.h"

/**
 * This structure
 * that represents
 * a date.
 */
typedef struct STRUCT_DATE
{
  int iDay;
  int iMonth;
  int iYear;
} STRUCT_DATE, *PSTRUCT_DATE;

/**
 * Structure that represents a address
 */
typedef struct STRUCT_ADDRESS
{
  char szStreet[64];
  int iNUmber;
  char szApartment[64];
  char szNeighborhood[64];
  char szCity[64];
  char szState[64];
  char szCEP[64]; /* In Brazil */
  char szZIP[64]; /* In USA    */
  char szCountry[64];
} STRUCT_ADDRESS, *PSTRUCT_ADDRESS;

/**
 * Structure that represents a
 * generic person.
 */
typedef struct STRUCT_PERSON
{
  STRUCT_ADDRESS stAddress;
  char szName[192];
  char szPhone[64];
  char szEmail[64];
} STRUCT_PERSON, *PSTRUCT_PERSON;

/**
 * Structure that represents a natural person.
 */
typedef struct STRUCT_NATURAL_PERSON
{
  STRUCT_PERSON stPersonInfo;
  char szFirstName[64];
  char szMiddleName[64];
  char szLastName[64];
  char szCPF[64]; /* In Brazil */
  char szSSN[64]; /* In USA    */
  STRUCT_DATE stBornDate;
  int iAge;
  char szNationality[64];
  char szMaritalStatus[64];
  char chSex; /* M or F */
} STRUCT_NATURAL_PERSON, *PSTRUCT_NATURAL_PERSON;

/******************************************************************************
 *                                                                            *
 *                                   JSON                                     *
 *                                                                            *
 ******************************************************************************/

STRUCT_NATURAL_PERSON gstPerson;

/**
 * {
 *   "nome": "Meu nome",
 *   "age": 21,
 *   "phone": "4686-5626",
 *   "email": "email@example.com",
 *   "CPF": "466.423.893-71",
 *   "nationality": "brazilian",
 * }
 */
STRUCT_JSON astJsonPerson[] = {
  { "nome",        JSONTYPE_STR,  sizeof(gstPerson.stPersonInfo.szName),  gstPerson.stPersonInfo.szName  },
  { "age",         JSONTYPE_INT,  sizeof(gstPerson.iAge),                 &gstPerson.iAge                },
  { "phone",       JSONTYPE_STR,  sizeof(gstPerson.stPersonInfo.szPhone), gstPerson.stPersonInfo.szPhone },
  { "email",       JSONTYPE_STR,  sizeof(gstPerson.stPersonInfo.szEmail), gstPerson.stPersonInfo.szEmail },
  { "CPF",         JSONTYPE_STR,  sizeof(gstPerson.szCPF),                gstPerson.szCPF                },
  { "nationality", JSONTYPE_STR,  sizeof(gstPerson.szNationality),        gstPerson.szNationality        },
  { NULL,          JSONTYPE_NULL, 0,                                      NULL                           }
};

/******************************************************************************
 *                                                                            *
 *                                   main                                     *
 *                                                                            *
 ******************************************************************************/
int main(void)
{
  char *pszJSON = NULL;
  PSTRUCT_JSON pstTmpJSON = astJsonPerson;

  if(!iJSON_Read(&pszJSON, "person.json"))
  {
    fprintf(stderr, "E: Impossivel ler o arquivo person.json");

    if(pszJSON)
    {
      free(pszJSON);
      pszJSON = NULL;
    }

    return -1;
  }

  printf("JSON lido:\n");
  printf("%s\n", pszJSON);

  if(!iJSON_LoadKeys(pszJSON, &pstTmpJSON))
  {
    fprintf(stderr, "E: Erro ao carregar JSON!");

    free(pszJSON);
    pszJSON = NULL;

    return -1;
  }

  printf("Dados coletados do JSON:\n");
  printf
  (
    "{\n"
    "  \"nome\": \"%s\",\n"
    "  \"age\": %d,\n"
    "  \"phone\": \"%s\",\n"
    "  \"email\": \"%s\",\n"
    "  \"CPF\": \"%s\",\n"
    "  \"nationality\": \"%s\"\n"
    "}\n", gstPerson.stPersonInfo.szName,
         gstPerson.iAge,
         gstPerson.stPersonInfo.szPhone,
         gstPerson.stPersonInfo.szEmail,
         gstPerson.szCPF,
         gstPerson.szNationality
  );

  free(pszJSON);
  pszJSON = NULL;

  if(!iJSON_DumpJSON(&pszJSON, pstTmpJSON))
  {
    return -1;
  }

  printf("\nCONTEUDO DA STRING JSON:\n");
  printf("%s", pszJSON);

  free(pszJSON);
  pszJSON = NULL;

  return 0;
}
