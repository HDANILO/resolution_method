#include "main.h"

int main()
{

	/*LinkedList<atomic>* ll = atomic::atomic_from_string(*new string("{a1,~a12,b123,~b1234}"));
	for(int i = 0; i < ll->size; i++)
		printf("Atomo: %s, negate: %s\n",ll->get(i)->atom.c_str(),(ll->get(i)->negate == true ? "true" : "false"));
	
	system("pause");
	exit(1);*/

	char * cformula = (char*)malloc(sizeof(char)*1024);
	string formula("");
	string tableaux("");
	printf("Digite a formula na forma clausal para resolver no sistema de resolucao:\n");
	printf("Por exemplo: {{a12,b},{~a,b},{a,~b32},{~a,~b},{a},{~bade}} onde ~ representa operador not.\n");
	printf("Mesmo que seja apenas a formula {a}, ela deve ser representada da seguinte maneira: {{a}}\n");
	printf("Podera ser usado qualquer indice apos a letra, por exemplo {{a12312731283}}\n");
	printf("Nao podera ser utilizado dupla negacao, ja que esta eh redudante\n");

	scanf("%s",cformula);
	formula = cformula;
	LinkedList< LinkedList<atomic> > *lla = atomic::atomic_from_formula(formula);
	int size = formula.length();
	int cont = 1;
	char* s = (char*)malloc(sizeof(char)*256);
	sprintf(s, "%d", cont);
	tableaux.append(s);
	tableaux.append(". ");
	for(int i = 1; i < size-1; i++)
	{
		if (formula.at(i) != '}')
		{			
			tableaux.append(formula.substr(i,1));
		}
		else
		{
			cont++;
			sprintf(s, "%d", cont);
			tableaux.append("}\n");
			tableaux.append(s);
			tableaux.append(". ");
			i++;
		}
	}
	
	while(atomic::iteract_tableaux(lla))
	{
		printf("Resolvendo Tableaux pelo metodo de resolucao\n");
		//do nothing
	}
	printf("Tableaux resolvido\n");
	//começa sistema de resolucao
	for(int i = 0; i < lla->size; i++)
	{
		printf("%d. {", i+1);
		if (lla->get(i)->size > 0)
		{
			for(int j = 0; j < lla->get(i)->size; j++)
			{
				if (j != lla->get(i)->size - 1)
					printf("%s,",lla->get(i)->get(j)->toString().c_str());
				else
					printf("%s}\n",lla->get(i)->get(j)->toString().c_str());
			}
		}
		else
			printf("}\n");
	}

	//printf("%s\n",tableaux.c_str());

	return 0;
}