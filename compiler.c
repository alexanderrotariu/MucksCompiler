#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "compiler.h"

//An instruction type has the tokens and the number of Tokens

//For each token you get an array
//In the array it reads each character from left to right
//Determine if it is a number or a variable
//Determine the arm operation being done
//After that you can find the op code and the shtamt
// REGISTER NUMBERS DO NOT MATTER. ALL THAT MATTERS IS THAT THE PROPER
//VALUES ARE STORED

//GLOBAL VARS
int registerCounter = 0;
char variablesUsed[32];
//int variableValue[32];
int varRegister[32];
int variablesUsedCounter = 0;
//int variableValueCounter = 0;

void convertCode(Instruction instruction)
{

    for(int i = 0; i < instruction.numTokens; i++)
    {
              //If you encounter a '=' this means you have to remove
            if(strcmp(instruction.tokens[i], "=") == 0)
            {
              bool overwrite = false;
                //If there are 3 tokens, that means its just gonna be an assignment
                //and if the number being assignment is a number
                if(instruction.numTokens == 3 && atoi(instruction.tokens[i+1]) > 0 )
                {
                  for(int j = 0; j < 32; j++)
                  {
                    if(instruction.tokens[i-1][0] == variablesUsed[j])
                    {
                      //varRegister[j] = registerCounter;
                      printf("MOV R%d, #%s\n", varRegister[j], instruction.tokens[i+1]);

                      overwrite = true;
                    }
                  }

                  if(overwrite == false)
                  {
                    printf("MOV R%d, #%s\n", registerCounter, instruction.tokens[i+1]);

                    variablesUsed[variablesUsedCounter] = instruction.tokens[i-1][0];
                    variablesUsedCounter++;
                    varRegister[registerCounter] = registerCounter;
                    registerCounter++;
                  }

                }
                else
                {
                  //ADD
                  if(strcmp(instruction.tokens[i + 2], "+") == 0)
                  {
                    //If both operands are both variables
                    char operand1 = instruction.tokens[i+1][0];
                    char operand2 = instruction.tokens[i+3][0];

                    if((operand1 >= 97 && operand1 <=122) && (operand2 >= 97 && operand2 <=122) )
                    {
                      int reg1 = 0;
                      int reg2 = 0;

                      //FINDING THE VALUE FOR OPERAND 1
                      for(int j = 0; j < 32; j++)
                      {
                        if(variablesUsed[j] == instruction.tokens[i+1][0])
                        {
                          reg1 = varRegister[j];
                          j = 32;
                        }
                      }
                      //FINDING THE VALUE FOR OPERAND 2
                      for(int j = 0; j < 32; j++)
                      {
                        if(variablesUsed[j] == instruction.tokens[i+3][0])
                        {
                          reg2 = varRegister[j];
                          j = 32;


                          printf("ADD R%d, R%d, R%d\n", registerCounter, reg1, reg2);

                          //printf("MOV R%d, R%d\n", registerCounter+1, registerCounter);

                        }
                      }
                      variablesUsed[variablesUsedCounter] = instruction.tokens[i-1][0];
                      variablesUsedCounter++;
                      varRegister[registerCounter] = registerCounter;
                      registerCounter++;
                    }
                      //IF 1 VARIABLE AND ONE NUMBER
                    else if((operand1 >= 97 && operand1 <=122) && (operand2 >= 48 && operand2 <=57))
                    {
                      int reg1 = 0;

                      //finding the value of operand1
                      for(int j = 0; j < 32; j++)
                      {
                        if(variablesUsed[j] == instruction.tokens[i+1][0])
                        {
                          reg1 = varRegister[j];
                          j = 32;
                        }
                      }

                      //Take the number out of the string
                      char temp[10];
                      for(int j = 0 ; j < strlen(instruction.tokens[i+3]); j++)
                      {
                        temp[j] = instruction.tokens[i+3][j];
                      }

                      int operandNum = atoi(temp);

                      printf("ADD R%d, R%d, #%d\n", registerCounter, reg1, operandNum);
                      //printf("MOV R%d, R%d\n", registerCounter+1, registerCounter);

                      variablesUsed[variablesUsedCounter] = instruction.tokens[i-1][0];
                      variablesUsedCounter++;
                      varRegister[registerCounter] = registerCounter;
                      registerCounter++;

                    }
                    //IF ONE NUMBER AND ONE VARIABLE
                    else if((operand1 >= 48 && operand1 <=57) && (operand2 >= 97 && operand2 <=122))
                    {
                      int reg2 = 0;

                      //finding the value of operand1
                      for(int j = 0; j < 32; j++)
                      {
                        if(variablesUsed[j] == instruction.tokens[i+3][0])
                        {
                          reg2 = varRegister[j];
                          j = 32;
                        }
                      }

                      //Take the number out of the string
                      char temp[10];
                      for(int j = 0 ; j < strlen(instruction.tokens[i+1]); j++)
                      {
                        temp[j] = instruction.tokens[i+1][j];
                      }

                      int operandNum = atoi(temp);

                      printf("ADD R%d, #%d, R%d\n", registerCounter, operandNum, reg2);
                      //printf("MOV R%d, R%d\n", registerCounter+1, registerCounter);

                      variablesUsed[variablesUsedCounter] = instruction.tokens[i-1][0];
                      variablesUsedCounter++;
                      varRegister[registerCounter] = registerCounter;
                      registerCounter++;



                    }
                    //IF 2 NUMBERS
                    else if((operand1 >= 48 && operand1 <=57) && (operand2 >= 48 && operand2 <=57))
                    {
                      char temp[10];
                      for(int j = 0 ; j < strlen(instruction.tokens[i+1]); j++)
                      {
                        temp[j] = instruction.tokens[i+1][j];
                      }

                      int operandNum1 = atoi(temp);

                      char temp2[10];
                      for(int j = 0 ; j < strlen(instruction.tokens[i+3]); j++)
                      {
                        temp2[j] = instruction.tokens[i+3][j];
                      }

                      int operandNum2 = atoi(temp2);

                      printf("ADD R%d, #%d, #%d\n", registerCounter, operandNum1, operandNum2);
                      //printf("MOV R%d, R%d\n", registerCounter+1, registerCounter);

                      variablesUsed[variablesUsedCounter] = instruction.tokens[i-1][0];
                      variablesUsedCounter++;
                      varRegister[registerCounter] = registerCounter;
                      registerCounter++;
                    }
                    else
                    {
                      printf("ERROR: ENTERED PARAMETERS DO NOT FOLLOW MUCKS SYNTAX\n");
                    }

                  }
                  //TO DO IMPLEMENT THE SUB FUNCTION
                  //TO DO SAVE WHAT VARIABLE IS WHAT REGISTER AFTER ADDITION
                  //IE. SAVE CURRENT REGISTER BEING WRITTEN TO CURRENT VARIABLE. FOR USE LATER.

//SUB--------------------------------------------------------------------------------------
                  else if(strcmp(instruction.tokens[i + 2], "-") == 0)
                  {
                    //If both operands are both variables
                    char operand1 = instruction.tokens[i+1][0];
                    char operand2 = instruction.tokens[i+3][0];

                    if((operand1 >= 97 && operand1 <=122) && (operand2 >= 97 && operand2 <=122) )
                    {
                      int reg1 = 0;
                      int reg2 = 0;

                      //FINDING THE VALUE FOR OPERAND 1
                      for(int j = 0; j < 32; j++)
                      {
                        if(variablesUsed[j] == instruction.tokens[i+1][0])
                        {
                          reg1 = varRegister[j];
                          j = 32;
                        }
                      }
                      //FINDING THE VALUE FOR OPERAND 2
                      for(int j = 0; j < 32; j++)
                      {
                        if(variablesUsed[j] == instruction.tokens[i+3][0])
                        {
                          reg2 = varRegister[j];
                          j = 32;

                        //  printf("reg 1 is: %d\n", reg1);
                        //  printf("reg 2 is: %d\n", reg2);

                          printf("SUB R%d, R%d, R%d\n", registerCounter, reg1, reg2);

                          //printf("MOV R%d, R%d\n", registerCounter+1, registerCounter);

                          variablesUsed[variablesUsedCounter] = instruction.tokens[i-1][0];
                          variablesUsedCounter++;
                          varRegister[registerCounter] = registerCounter;
                          registerCounter++;
                        }
                      }
                    }
                      //IF 1 VARIABLE AND ONE NUMBER
                    else if((operand1 >= 97 && operand1 <=122) && (operand2 >= 48 && operand2 <=57))
                    {
                      int reg1 = 0;

                      //finding the value of operand1
                      for(int j = 0; j < 32; j++)
                      {
                        if(variablesUsed[j] == instruction.tokens[i+1][0])
                        {
                          reg1 = varRegister[j];
                          j = 32;
                        }
                      }

                      //Take the number out of the string
                      char temp[10];
                      for(int j = 0 ; j < strlen(instruction.tokens[i+3]); j++)
                      {
                        temp[j] = instruction.tokens[i+3][j];
                      }

                      int operandNum = atoi(temp);

                      printf("SUB R%d, R%d, #%d\n", registerCounter, reg1, operandNum);
                      //printf("MOV R%d, R%d\n", registerCounter+1, registerCounter);

                      variablesUsed[variablesUsedCounter] = instruction.tokens[i-1][0];
                      variablesUsedCounter++;
                      varRegister[registerCounter] = registerCounter;
                      registerCounter++;

                    }
                    //IF ONE NUMBER AND ONE VARIABLE
                    else if((operand1 >= 48 && operand1 <=57) && (operand2 >= 97 && operand2 <=122))
                    {
                      int reg2 = 0;

                      //finding the value of operand1
                      for(int j = 0; j < 32; j++)
                      {
                        if(variablesUsed[j] == instruction.tokens[i+3][0])
                        {
                          reg2 = varRegister[j];
                          j = 32;
                        }
                      }

                      //Take the number out of the string
                      char temp[10];
                      for(int j = 0 ; j < strlen(instruction.tokens[i+1]); j++)
                      {
                        temp[j] = instruction.tokens[i+1][j];
                      }

                      int operandNum = atoi(temp);

                      printf("SUB R%d, #%d, R%d\n", registerCounter, operandNum, reg2);
                      //printf("MOV R%d, R%d\n", registerCounter+1, registerCounter);

                      variablesUsed[variablesUsedCounter] = instruction.tokens[i-1][0];
                      variablesUsedCounter++;
                      varRegister[registerCounter] = registerCounter;
                      registerCounter++;



                    }
                    //IF 2 NUMBERS
                    else if((operand1 >= 48 && operand1 <=57) && (operand2 >= 48 && operand2 <=57))
                    {
                      char temp[10];
                      for(int j = 0 ; j < strlen(instruction.tokens[i+1]); j++)
                      {
                        temp[j] = instruction.tokens[i+1][j];
                      }

                      int operandNum1 = atoi(temp);

                      char temp2[10];
                      for(int j = 0 ; j < strlen(instruction.tokens[i+3]); j++)
                      {
                        temp2[j] = instruction.tokens[i+3][j];
                      }

                      int operandNum2 = atoi(temp2);

                      printf("SUB R%d, #%d, #%d\n", registerCounter, operandNum1, operandNum2);
                      
                      variablesUsed[variablesUsedCounter] = instruction.tokens[i-1][0];
                      variablesUsedCounter++;
                      varRegister[registerCounter] = registerCounter;
                      registerCounter++;
                    }
                    else
                    {
                      printf("ERROR: ENTERED PARAMETERS DO NOT FOLLOW MUCKS SYNTAX\n");
                    }

                  }
                }

            }

    }
}
