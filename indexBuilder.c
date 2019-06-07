/*
*SWE2007: System Software Experiment 2 (Fall 2018)
*
* Skeleton code for PA#1
*
* October 17, 2018.
* Sungkyunkwan University
*
* Student Id   : 2014311945
* Student Name : 이 보 형
*
*-----------------------------------------------------------
*/

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MAX_BUF_LIMIT 1000000

typedef struct index_node* index_ptr;
typedef struct index_node {
	char word[30];
	int word_count;
	char loc[4000][20]; // 중복 단어 위치를 저장
	index_ptr left_child;
	index_ptr right_child;
}index_node;
index_ptr p = NULL;
index_ptr *T = &p;

int index_num = 0; //인덱스 개수
int word_num = 0; //총 단어 수
char chap[3] = {'\0',}; // 장 개수
int sen = 0; // 절 개수
const char *name;
int errno;
char index_data[1000000];

//파일을 라인별로 저장하기 위한 변수
char *lineBuf;
int lineBufSize;
char **line;
int line_Num;
int lineBufLimit = 500;
int lineArrLimit = 500;
char buf[MAX_BUF_LIMIT+1];
char* word_loc(char *arr1, char *arr2){ //단어와 단어 위치 string을 concantrate
	char *temp = (char*)malloc(sizeof(char)*30); int i, j;
	for(i = 0;arr1[i] != '\0';i++)
		temp[i] = arr1[i];
	temp[i] = ' ';
	for(j = 0; arr2[j] != '\0';j++)
		temp[++i] = arr2[j];
	temp[i+1] = '\n';
	temp[i+2] = '\0';
	return temp;
}

int word_Comp(char *arr1, char* arr2){
	int i = 0;
	while (arr1[i] != '\0' || arr2[i] != '\0') {
		if (arr1[i] >= 'A' && arr1[i] <= 'Z')
			arr1[i] = arr1[i] + 32;
		if (arr2[i] >= 'A' && arr2[i] <= 'Z')
			arr2[i] = arr2[i] + 32;
		if (arr1[i] != arr2[i])
			return arr1[i] - arr2[i];
		i++;
	}
	return 0;
}

void word_cat(char* arr1, char*arr2){
	static int i = 0;
	for(int j = 0;arr2[j] != '\0';j++){
		arr1[i++] = arr2[j];
	}
}

void word_Copy(char *arr1, char *arr2) {
	int i;
	for (i = 0; arr2[i] != '\0'; i++) {
		arr1[i] = arr2[i];
	}
	arr1[i] = '\0';
}

int word_Length(char *arr) {
	int i = 0;
	while (arr[i] != '\0') {
		i++;
	}
	return i;
}

void strreverse(char *begin, char * end) {
	char aux; 
	while (end>begin)
		aux = *end, *end-- = *begin, *begin++ = aux; 
}

void int2str(int value, char *str, int base) { 
	static char num[] = "0123456789abcdefghijklmnopqrstuvwxyz"; 
	char *wstr = str; int sign; 
	if (base<2 || base>35) { 
		*wstr = '\0'; 
		return; 
	} 
	if ((sign = value) <0) 
		value = -value; 
	do 
		*wstr++ = num[value%base]; 
	while (value /= base); 
	if (sign<0) 
		*wstr = '\0'; 
	strreverse(str, wstr - 1); 
}

void insert_node(index_ptr *root, char* key, char* loc) { //Tree에 데이터 삽입
	index_ptr p, t;
	index_ptr n;

	t = *root;
	p = NULL;

	while (t != NULL)
	{
		if (word_Comp(key, t->word) == 0) {
			t->word_count++;
			int i = 0;
			while (t->loc[i][0] >= '0' && t->loc[i][0] <= '9')
				i++;
			word_Copy(t->loc[i], loc);
			return;
		}
		p = t;
		if (word_Comp(key, t->word) < 0)
			t = t->left_child;
		else
			t = t->right_child;
	}

	//트리에 데이터가 존재하지 않으면 
	n = (index_ptr)malloc(sizeof(index_node));

	if (n == NULL)
		return;

	// 새로운 노드 데이터 삽입
	word_Copy(n->word, key);
	word_Copy(n->loc[0], loc);
	n->word_count = 1;
	index_num++;
	n->left_child = n->right_child = NULL;

	if (p != NULL)
	{
		if (word_Comp(key, p->word) < 0)
			p->left_child = n;
		else
			p->right_child = n;
	}
	else
		*root = n;
}

void inorder(index_ptr root) {
	char temp[3] = {':', ' ','\0'}; char temp2[3] = {',', ' ','\0'}; char temp3[2] = {'\n','\0'}; char wc[5] = {'\0',}; char space[2] = {' ', '\0'};
	if (root) {
		inorder(root->left_child);
		word_cat(index_data,root->word);
		word_cat(index_data,temp);
		int2str(root->word_count,wc,10); 
		word_cat(index_data,wc);
		word_cat(index_data,space);
		for (int i = 0;i<root->word_count; i++) {
			if (root->loc[i][0] >= '0' && root->loc[i][0] <= '9'){
				word_cat(index_data, root->loc[i]);
				if(i != root->word_count - 1)
					word_cat(index_data, temp2);
				else
					word_cat(index_data, temp3);
			}
		}
		inorder(root->right_child);
	}
}

void readLine(int fd) { // 파일을 라인별로 읽어 저장
	int size;
	
	lineBuf = (char*)malloc(lineBufLimit * sizeof(char));
	lineBufSize = 0;
	
	line = (char**)malloc(lineArrLimit * sizeof(char*));
	line_Num = 0;

		size = read(fd, buf, MAX_BUF_LIMIT);
	
		for (int i = 0; i < size; i++) {
			if(buf[i] == '\0')
				break;
	
			if (buf[i] == '\n') {
	
				if (line_Num == lineArrLimit) {
					lineArrLimit += 100;
					line = (char**)realloc(line, lineArrLimit * sizeof(char*));
				}
	
				line[line_Num] = (char*)malloc(lineBufSize * sizeof(char) + 1);
	
				for (int j = 0; j < lineBufSize; j++)
					line[line_Num][j] = lineBuf[j];
				line[line_Num][lineBufSize] = '\0';
				lineBufSize = 0;
				line_Num++;
				continue;
			}
	
			if (lineBufSize == lineBufLimit) {
				lineBufLimit += 100;
				lineBuf = (char*)realloc(lineBuf, lineBufLimit * sizeof(char));
			}
			lineBuf[lineBufSize++] = buf[i];
		}
}

void indexBuilder(const char* inputFileNm, const char* indexFileNm) {
	name = inputFileNm;
	int fd_input; int fd_index; char word[50]; char loc[20]; int WordState = 0; int k = 0; int l = 0;
	char ch[4] = { '\0', }; int temp; int i; int start_line = 0;
	int fd_bible;
	fd_input = open(inputFileNm, O_RDONLY);
	fd_index = open(indexFileNm, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	fd_bible = open("bible.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
	readLine(fd_input);
	
	for(i = 0; i<line_Num; i++){
		if ((line[i][0] >= '0' && line[i][0] <= '9') || line[i][0] == ' ') {
		if(line[i][0] == ' '){
			for(l = 1; line[i][l] != ' ';l++){
				loc[l-1] = line[i][l];
			}
		temp = l -1;
		}
		else{
			for (l = 0; line[i][l] != ' '; l++) {
				loc[l] = line[i][l];
			}
		temp = l;
		}
			for (int j = 0; j < word_Length(line[i])+1; j++) {
				if (line[i][j] == ' ' || line[i][j] == '\0') {
					if (WordState == 1) {
						word[k] = '\0';
						loc[l] = '\0';
						insert_node(T, word, loc);
						WordState = 0;
						word_num++;
						l = temp; k = 0; ch[1] = '\0'; ch[2] = '\0';
					}
				}

				else if ((line[i][j] >= 'A' && line[i][j] <= 'Z') || (line[i][j] >= 'a' && line[i][j] <= 'z') || line[i][j] == '\'' || line[i][j] == '-') {
					WordState = 1;
					word[k++] = line[i][j];
					if (l == temp) {
						int2str(j-(temp+1), ch, 10);
						for (int m = 0; ch[m] != '\0'; m++) {
							loc[l++] = ch[m];
						}
					}
				}
			}
		}
		else
			start_line++;
	}
	i = i -(start_line); //numbers of sen 
	if(line[i-1][0] == ' '){
		chap[0] = line[i-1][1]; 
		chap[1] = line[i-1][2];
	}
	else{
		chap[0] = line[i-1][0]; chap[1] = line[i-1][1];
	}
	sen = i;
	inorder(*T);
	errno = write(fd_index, index_data, strlen(index_data));
	errno = write(fd_bible, inputFileNm, strlen(inputFileNm));
	errno = write(fd_bible, " ", 1);
	errno = write(fd_bible, indexFileNm, strlen(indexFileNm));
	errno = write(fd_bible, "\n", 1);
	
	close(fd_bible);
	close(fd_input);
	close(fd_index);
}

