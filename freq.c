

/* Programa que gera um arquivo de texto com a frequencia absoluta e relativa das palavras de um livro */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#ifdef _WIN32
	#define CLEAR system("cls")
#else
	#define CLEAR system("clear")
#endif

typedef enum {
	OPTION_FREQUENCY = 1, /* 1 */
	OPTION_FILE, /* 2 */
	OPTION_QUIT, /* 3 */
} OptionMain;

typedef struct {
	int fr, fab;
} palavra;

void showText(FILE *fp_text) {
	char aux2[1001] = "xxx", text[1001], aux;

	fseek(fp_text,0,SEEK_SET);
	
	while(fgets(text,1000,fp_text)) {

		printf("%s",text);
	}

	/* Ou assim */
	// while(fscanf(fp_text,"%c",&aux) == 1) {
	// 	printf("%c",aux);
	// }
	printf("\n");
}

int menuMain(void) {
	int escolha;

	do {
		printf("\t%-20s\n\n","Frequencia de Palavras");
		printf("\t%-20s\n\n","Opcoes");
		printf("1 - Pesquisar em livro/texto\n");
		printf("2 - Consultar arquivo\n");
		printf("3 - Sair\n");

		printf("Opcao: ");
		scanf("%d%*c",&escolha);

		if (escolha <= 0 || escolha > 3) {
			printf("\aEscolha invalida!\n");
			printf("Aperte <Enter> para continuar... ");
			getchar();
			CLEAR;
		}

	} while(escolha <= 0 || escolha > 3);

	return escolha;
}

FILE *openFile() {
	FILE *fp_text;
	char path[1001];

	printf("\t%-20s\t\n\n","Pesquisar em livro/texto");

	do {
		printf("Digite o caminho: ");
		scanf("%[^\n]%*c",path);

		if (strlen(path) >= 900) {
			printf("Caminho invalido!\n");
		}

	} while(strlen(path) >= 900);

	/* Tenta abrir o arquivo */

	fp_text = fopen(path,"r+");

	if (fp_text == NULL) {
		printf("\nArquivo nao encontrado!\n");
		return NULL;
	}
	else {
		return fp_text;
	}

}

void palavras(FILE *fp_text) {
	char word[1001], wordAux[1001], **words;
	int i, j, k, linhas = 1, colunas = 1001;

	/* Quantidade inicial de memoria alocada */
	words = (char**) malloc(sizeof(char*)*linhas);

	for(k=0;k<linhas;k++) {
		words[k] = (char*) malloc(sizeof(char)*colunas);
	}

	rewind(fp_text);
	k = 0;
	while(fscanf(fp_text,"%s",word) != EOF) {
		
		/* Loop para ler letra por letra e pular a pontuacao */
		i = j = 0;
		while(word[i] != '\0') {

			if (word[i] != '.' && word[i] != '*' && word[i] != ',' && word[i] != ';' && word[i] != '!' && word[i] != '?') {
				wordAux[j] = word[i];
				j++;
			}
			i++;
		}

		wordAux[j] = '\0';
		
		strcpy(words[k],wordAux);
		k++;

		/* Aumenta o tamanho da matriz */
		linhas++;
		words = (char**) realloc(words,sizeof(char*)*linhas);
		words[linhas-1] = (char*) malloc(sizeof(char)*colunas);

	}




	for(i=0;i<k;i++) {
		printf("%s ",words[i]);
	} 

	printf("\n");

	/* Desaloca memoria */
	for(k=0;k<linhas;k++) {
		free(words[k]);
	}

	free(words);

}

void frequencia(void) {
	FILE *fp_text;
	char opcao;


	do {
		CLEAR;
		fp_text = openFile();

		if (fp_text != NULL) {

			showText(fp_text);

			fclose(fp_text);
		}

		printf("Outro arquivo? (S/N) ");
		scanf("%c%*c",&opcao);


	} while(toupper(opcao) == 'S');

	printf("Aperte <Enter> para retornar ao menu principal...");
	getchar();
}


void quit() {

	CLEAR;
	printf("Aperte Enter para sair... ");
	getchar();
	CLEAR;
}

int main(void) {
	int opcao;

	do {
		CLEAR;
		opcao = menuMain();

		switch(opcao) {
			case OPTION_FREQUENCY : frequencia(); break;

			case OPTION_QUIT : quit(); break;
		};

	} while(opcao != OPTION_QUIT);


	return 0;
}

