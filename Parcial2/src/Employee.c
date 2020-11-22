#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include "utn.h"
#include "employee.h"

static int UpperFirstChar(char *string);

/** \brief Capitalizes the first letter of a string
 *
 * \param string char* : string to capitalize the first character.
 * \return int output : (-1) If there was an error (0) if the process was successful.
 */
static int UpperFirstChar(char *string)
{
	int functionReturn = -1;
	if(string!=NULL)
	{
		char bufferName[LONG_NAME];
		strncpy(bufferName, string, LONG_NAME);
		bufferName[0] = toupper(bufferName[0]);
			for(int i=1;i<LONG_NAME;i++)
			{
				bufferName[i] = tolower(bufferName[i]);
			}
		strncpy(string, bufferName, LONG_NAME);
		functionReturn = 0;
	}
	return functionReturn;
}

/** \brief Set an id to an employee
 *
 * \param id int : Id that will be assigned to the employee
 * \return int output : (-1) If there was an error (0) if the process was successful.
 */
int employee_setId(Employee* this,int id)
{
	int output=-1;
	if(this!=NULL && id>-1)
	{
		this->id = id;
		output=0;
	}
	return output;
}

/** \brief Get an id to an employee
 *
 * \param id int* : Pointer that will have the memory address of the id obtained
 * \return int output : (-1) If there was an error (0) if the process was successful.
 */
int  employee_getId(Employee* this,int* id)
{
	int output=-1;
	if(this!=NULL && id!=NULL)
	{
		*id = this->id;
		output=0;
	}
	return output;
}

/** \brief Set a string as the name of an employee
 *
 * \param nombre char* : String as name to an employee
 * \return int output : (-1) If there was an error (0) if the process was successful.
 */
int employee_setNombre(Employee* this,char* nombre)
{
	int output=-1;
	if(this!=NULL && isString(nombre)==1 && nombre!=NULL)
	{
		strncpy(this->nombre,nombre,LONG_NAME);
		UpperFirstChar(this->nombre);
		output=0;
	}
	return output;
}

/** \brief Gets the name of an employee
 *
 * \param nombre char* : Pointer that will have the memory address of the employee's name
 * \return int output : (-1) If there was an error (0) if the process was successful.
 */
int employee_getNombre(Employee* this,char* nombre)
{
	int retornar=-1;
	if(this!=NULL && nombre!=NULL)
	{
		strncpy(nombre, this->nombre, LONG_NAME);
		retornar=0;
	}
	return retornar;
}

/** \brief Set an amount of hours to an employee
 *
 * \param horasTrabajadas int : Amounts of hours worked
 * \return int output : (-1) If there was an error (0) if the process was successful.
 */
int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
	int output=-1;
	if(this!=NULL && horasTrabajadas>0)
	{
		this->horasTrabajadas = horasTrabajadas;
		output=0;
	}
	return output;

}

/** \brief Get the number of hours worked by an employee
 *
 * \param horasTrabajadas int* : Pointer that will have the memory address of the hours worked of an employee
 * \return int output : (-1) If there was an error (0) if the process was successful.
 */
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
	int output=-1;
	if(this!=NULL && horasTrabajadas!=NULL)
	{
		*horasTrabajadas = this->horasTrabajadas;
		output=0;
	}
	return output;

}

/** \brief Set a salary for an employee
 *
 * \param sueldo int : Salary which will be applied to an employee
 * \return int output : (-1) If there was an error (0) if the process was successful.
 */
int employee_setSueldo(Employee* this,int sueldo)
{
	int output=-1;
	if(this!=NULL && sueldo>0)
	{
		this->sueldo = sueldo;
		output=0;
	}
	return output;

}

/** \brief Get an employee's salary
 *
 * \param sueldo int* : Pointer that will obtain the memory address of an employee's salary
 * \return int output : (-1) If there was an error (0) if the process was successful.
 */
int employee_getSueldo(Employee* this,int* sueldo)
{
	int output=-1;
	if(this!=NULL && sueldo!=NULL)
	{
		*sueldo= this->sueldo;
		output=0;
	}
	return output;

}


/** \brief Set an id of type character to an employee
 *
 * \param id char* : Id which will set the employee
 * \return int output : (-1) If there was an error (0) if the process was successful.
 */
int employee_setIdStr(Employee* this, char* id)
{
	int retornar=-1;
	char bufferId[SIZE];
	if(this!=NULL && id!=NULL && isInt(id)==1)
	{
		strncpy(bufferId, id, SIZE);
		this->id = atoi(bufferId);
		retornar=0;
	}
	return retornar;
}

/** \brief Returns the string id of an employee
 *
 * \param id char* : Pointer that will obtain the memory address of the employee's id.
 * \return int output : (-1) If there was an error (0) if the process was successful.
 */
int employee_getIdStr(Employee* this,char* id)
{
	int output=-1;

	if(this!=NULL && id!=NULL)
	{
		sprintf(id,"%d",this->id);
		output=0;
	}
	return output;
}

/** \brief Set the number of hours worked
 *
 * \param horasTrabajadas char* : Amounts of hours worked
 * \return int output : (-1) If there was an error (0) if the process was successful.
 */
int employee_setHoursWorkedStr(Employee* this, char* horasTrabajadas)
{
	int output=-1;
	char buffer[SIZE];
	if(this!=NULL && horasTrabajadas!=NULL && isInt(horasTrabajadas)==1)
	{
			strncpy(buffer, horasTrabajadas, SIZE);
			this->horasTrabajadas=atoi(buffer);
			output=0;
	}
	return output;
}

/** \brief Gets the number of hours worked by a customer
 *
 * \param horasTrabajadas char* : Amounts of hours worked
 * \return int output : (-1) If there was an error (0) if the process was successful.
 */
int employee_getHorasTrabajadasStr(Employee* this,char* horasTrabajadas)
{
	int output=-1;
	if(this!=NULL && horasTrabajadas!=NULL)
	{
		sprintf(horasTrabajadas,"%d",this->horasTrabajadas);
		output=0;
	}
	return output;
}

/** \brief Set an employee's salary
 *
 * \param sueldo char* : Amounts of salary
 * \return int output : (-1) If there was an error (0) if the process was successful.
 */
int employee_setSalaryStr(Employee* this, char* sueldo)
{
	int output=-1;
	char buffer[SIZE];
	if(this!=NULL && sueldo!=NULL && isInt(sueldo)==1)
	{
			strncpy(buffer, sueldo, SIZE);
			this->sueldo=atoi(buffer);
			output=0;
	}
	return output;
}

/** \brief Get an employee's salary
 *
 * \param sueldo char* : Pointer that will obtain the memory address of an employee's salary
 * \return int output : (-1) If there was an error (0) if the process was successful.
 */
int employee_getSueldoStr(Employee* this,char* sueldo)
{
	int output=-1;
	if(this!=NULL && sueldo!=NULL)
	{
		sprintf(sueldo,"%d",this->sueldo);
		output=0;
	}
	return output;
}

/** \brief Request memory to generate a new employee
 *
 */
Employee* employee_new()
{
	Employee* this;
	this=(Employee*)malloc(sizeof(Employee));
	return this;
}

/** \brief Method to remove an employee.
 * \param this Employee* : Employee being removed
 */
void employee_delete(Employee* this)
{
	if(this!=NULL)
	{
		free(this);
	}
}

/** \brief Method to generate a new employee who will have all his data of type string.
 *
 * \param idStr char* : id that the new employee will be set
 * \param nombreStr char* : name that the new employee will be set
 * \param horasTrabajadasStr char* : worked hours that the new employee will be set
 * \param sueldo char* : salary that the new employee will be set
 * \return :  (NULL) If there was an error (this) if the process was successful.
 */
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldo)
{
	Employee* this = employee_new();
	if(this!=NULL)
	{
		if(  employee_setIdStr(this, idStr)!=-1 &&
		     employee_setNombre(this, nombreStr)!=-1 &&
			 employee_setHoursWorkedStr(this, horasTrabajadasStr)!=-1 &&
			 employee_setSalaryStr(this, sueldo)!=-1)
		{
			return this;
		}
	}
	employee_delete(this);
	return NULL;
}

/** \brief Method to generate a new employee who will have all his data of type string.
 *
 * \param idStr char* : id that the new employee will be set
 * \param nombreStr char* : name that the new employee will be set
 * \param horasTrabajadasStr char* : worked hours that the new employee will be set
 * \param sueldo char* : salary that the new employee will be set
 * \return int output : (-1) If there was an error (0) if the process was successful.
 */
int employee_print(Employee* this)
{
	int output=-1;
	char nombreAux[SIZE];
	char idAux[SIZE];
	char horasAux[SIZE];
	char salarioAux[SIZE];
	if(this!=NULL)
	{

		if( employee_getNombre(this, nombreAux)==0			    &&
			employee_getIdStr(this, idAux)==0					&&
			employee_getHorasTrabajadasStr(this, horasAux)==0   &&
			employee_getSueldoStr(this, salarioAux)==0			)
		{
			printf("\nID     Nombre        Horas      Sueldo\n");
			printf("%-6s %-10s  %5s %12s\n", idAux, nombreAux, horasAux, salarioAux);
			output = 0;
		}
	}
	return output;
}



/** \brief Method to generate a new employee.
 *
 * \param id int* : id that the new employee will be set
 * \param name char* : name that the new employee will be set
 * \param hours int : worked hours that the new employee will be set
 * \param sueldo int : salary that the new employee will be set
 * \return int output : (-1) If there was an error (0) if the process was successful.
 */
Employee* employee_newParameters(int id,char* name,int hours, int salary)
{
	Employee* this = employee_new();
	if(this!=NULL)
	{
		if(  employee_setId(this, id)==0       				&&
		     employee_setNombre(this, name)==0 				&&
			 employee_setHorasTrabajadas(this, hours)==0    &&
			 employee_setSueldo(this, salary)==0			)
		{
			return this;
		}
	}
	employee_delete(this);
	return NULL;
}

/** \brief Alphabetical ordering method
 *
 * \param itemOne void* : argument on which it will be decided if one is greater than the other
 * \param itemTwo void* : argument on which it will be decided if one is greater than the other
 * \return int output : (1) If the first data is greater than the second (-1, 0) if the second data is greater than the first.
 */
int employee_sort(void* itemOne,void* itemTwo)
{
	int output=0;
	Employee* buffer1;
	Employee* buffer2;

	buffer1	 = itemOne;
	buffer2	 = itemTwo;

	char name_1[LONG_NAME];
	char name_2[LONG_NAME];

	if(employee_getNombre(buffer1, name_1)==0   &&
	   employee_getNombre(buffer2, name_2)==0	)
	{
		if( strncmp(name_1, name_2,LONG_NAME)>0)
		{
			output = 1;
		}
		else
		{
			output=-1;
		}
	}
	else
	{
		printf("\nThere was a mistake -> employee_sort(void* itemOne,void* itemTwo)");
	}

	return output;
}


/** \brief ID ordering method
 *
 * \param itemOne void* : argument on which it will be decided if one is greater than the other
 * \param itemTwo void* : argument on which it will be decided if one is greater than the other
 * \return int output : (1) If the first data is greater than the second (-1, 0) if the second data is greater than the first.
 */
int employee_sortID(void* itemOne,void* itemTwo)
{
	int output=0;
	Employee* buffer1;
	Employee* buffer2;
	int id1;
	int id2;
	buffer1	 = itemOne;
	buffer2	 = itemTwo;

	if(employee_getId(buffer1, &id1)==0   &&
	   employee_getId(buffer2, &id2)==0	  )
	{
		if(id1>id2)
			{
			output= 1;
			}
			else
			{
				if(id1<id2)
				{
					output= -1;
				}
				else
				{

				}
			}
	}
	else
	{
		printf("\nThere was a mistake-> employee_sort(void* itemOne,void* itemTwo)");
	}
	return output;
}

/* \brief  Elimina los empleados con sueldo mayor a x
 *
 *
 */
int employee_removeBy_Salary(void* itemOne) //FUNCIONA
{
	int output=-1;
	int auxSalary;
	Employee* buffer1;
	buffer1	 = itemOne;
	if(buffer1!=NULL)
	{
		employee_getSueldo(buffer1, &auxSalary);
		if(auxSalary>25000)
		{
			output=0;
		}
	}
	return output;
}

/* \brief
 *
 *
 */
int employee_printConMap(void* itemOne)
{
	int output=-1;
	Employee* buffer;
	buffer =(Employee*)itemOne;
	char bufferName[SIZE];
	char bufferId[SIZE];
	char bufferHours[SIZE];
	char bufferSalary[SIZE];
	if(buffer != NULL  							                &&
	   employee_getNombre(buffer, bufferName)==0                &&
	   employee_getIdStr(buffer, bufferId)==0                   &&
	   employee_getIdStr(buffer, bufferId)==0	 				&&
	   employee_getHorasTrabajadasStr(buffer, bufferHours)==0   &&
	   employee_getSueldoStr(buffer, bufferSalary)==0			 )
	{
		printf("%-8s %-15s %8s %12s\n", bufferId, bufferName, bufferHours, bufferSalary);
		output=0;
	}
	return output;
}

/* \brief
 *
 *
 */
int employee_getSalarioTotal(void* itemOne) //FUNCIONA
{
	int output=0;
	Employee* buffer1;
	buffer1	 = itemOne;
	if(buffer1!=NULL)
	{
		employee_getSueldo(buffer1, &output);
	}
	return output;
}


















