#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <pthread.h>

#define GETSIZE 100
#define MAX_BUF_LIMIT 1000000
#define MAXSIZE 1000000

typedef struct ReadByLine {
	char** line;
	int line_Num;
}ReadByLine;

int l =0;

int word_Comp(char *arr1, char* arr2){
	char temp1[30], temp2[30];
	strcpy(temp1, arr1); strcpy(temp2, arr2);
	int i = 0;
	while (temp1[i] != '\0' || temp2[i] != '\0') {
		if (temp1[i] >= 'A' && temp1[i] <= 'Z')
			temp1[i] = temp1[i] + 32;
		if (temp2[i] >= 'A' && temp2[i] <= 'Z')
			temp2[i] = temp2[i] + 32;
		if (temp1[i] != temp2[i])
			return temp1[i] - temp2[i];
		i++;
	}
	return 0;
}
	
char* CASE1_bracket(char (*keyword)[30], char *file_line, int k_i){
	char *res = (char*)malloc(sizeof(char)*500); int idx = 0; int i = 0; char file_word[30]; int fw_idx=0; int flag = 0;
	int WordState = 0; int p = 0;
	while(1){ // 장:절 부분 입력
		if(file_line[i] == ' ') break;
		res[idx++] = file_line[i];
		i++;
	}
	res[idx++] = file_line[i++];
	//file_line을 word별로 읽으며 keyword와 비교
	while(i<strlen(file_line)){
		p = i;
		flag = 0;
		while(1){
		if (file_line[i] == ' ' || file_line[i] == '\0') {
			if (WordState == 1) {
				WordState = 0;
				break;
			}
		}
		else if ((file_line[i] >= 'A' && file_line[i] <= 'Z') || (file_line[i] >= 'a' && file_line[i] <= 'z') || file_line[i] == '\'' || file_line[i] == '-') {
			WordState = 1;
			file_word[fw_idx++] = file_line[i];
		}
		i++;
		}
		file_word[fw_idx] = '\0'; fw_idx = 0; i++;
		for(int i = 0; i<k_i; i++){ //입력받은 keyword와 파일의 단어가 같은지 비교
			if(word_Comp(file_word, keyword[i]) == 0){
				flag = 1;
				break;
			}
		}
		if(flag == 0){ //키워드와 다른 단어일 경우
			for(int k = p; k < i; k++)
				res[idx++] = file_line[k];
		}	
		else{ // 키워드와 같은 단어일 경우
			res[idx++] = '[';
			for(int k = 0; file_word[k] != '\0'; k++){
				res[idx++] = file_word[k];
			}
			res[idx++] = ']';
			p = p + strlen(file_word);
			for(int k = p; k < i; k++)
				res[idx++] = file_line[k];
		}
	}
	res[idx-1] = '\0';
	return res;
}


void CASE1(char* ReturnPhrase, ReadByLine file_Line, char *search_idx, char(*keyword)[30], int k_i, char* file_Name){
	int i = 0, k = 0, s = 0; int start = 0; char ret[500];
		char temp[10]; char fileIdx_temp[10];
		for(int i = 0; i < file_Line.line_Num; i++){
			if ((file_Line.line[i][0] >= '0' && file_Line.line[i][0] <= '9') || file_Line.line[i][0] == ' ') break;
			else start++;
			// 1장1절이 나올 때까지 패스
		}
				
		while (i < strlen(search_idx)) { // 찾을 단어 장절 저장
			while (1) {
				if (search_idx[i] == ' ' || search_idx[i] == '\0') break;
				temp[k++] = search_idx[i];
				i++;
			}
			temp[k] = '\0'; k = 0;
			for (int j = start; j < file_Line.line_Num; j++) {
				while (1) { // 장:절: 까지 읽고 반환
					if (file_Line.line[j][s] == ' ') break;
					fileIdx_temp[k++] = file_Line.line[j][s];
					s++;
				}
				fileIdx_temp[k] = '\0'; k = 0; s = 0;
				if (strcmp(temp, fileIdx_temp) == 0) {
					strcpy(ret, CASE1_bracket(keyword, file_Line.line[j], k_i));
					for(int p = 0; p < strlen(file_Name);p++){
						ReturnPhrase[l++] = file_Name[p];
					}
					while (ret[s] != '\0') {
						ReturnPhrase[l++] = ret[s];
						s++;
					}
					ReturnPhrase[l++] = '\n';
					break;
				}
			}
			i++;
		}
}

char* CASE2_bracket(char (*keyword)[30], char *file_line, int k_i){
	char *res = (char*)malloc(sizeof(char)*500); int idx = 0; int i = 0; char file_word[30]; int fw_idx=0; int flag = 0;
	int WordState = 0; int p = 0, q = 0; char next_word[30]; char next_word2[30]; char next_word3[30]; char next_word4[30]; char next_word5[30]; char next_word6[30]; char next_word7[30]; char next_word8[30]; char next_word9[30]; int check = 0;
	while(1){ // 장:절 부분 입력
		if(file_line[i] == ' ') break;
		res[idx++] = file_line[i];
		i++;
	}
	res[idx++] = file_line[i++];
	//file_line을 word별로 읽으며 keyword와 비교
	while(i<strlen(file_line)){
		p = i;
		flag = 0;
		while(1){
		if (file_line[i] == ' ' || file_line[i] == '\0') {
			if (WordState == 1) {
				WordState = 0;
				break;
			}
		}
		else if ((file_line[i] >= 'A' && file_line[i] <= 'Z') || (file_line[i] >= 'a' && file_line[i] <= 'z') || file_line[i] == '\'' || file_line[i] == '-') {
			WordState = 1;
			file_word[fw_idx++] = file_line[i];
		}
		i++;
		}
		file_word[fw_idx] = '\0'; fw_idx = 0; i++;
		if(k_i == 1 && word_Comp(file_word, keyword[0]) == 0){
			flag = 1;
			check = 1;
		}
		//첫 번째 키워드와 같은 단어를 찾으면
		if(k_i > 1 && word_Comp(file_word, keyword[0]) == 0){
			//다음 단어가 두 번째 키워드와 같으면
			q = i;
			while(1){
				if (file_line[q] == ' ' || file_line[q] == '\0') {
					if (WordState == 1) {
						WordState = 0;
						break;
					}
				}
				else if ((file_line[q] >= 'A' && file_line[q] <= 'Z') || (file_line[q] >= 'a' && file_line[q] <= 'z') || file_line[q] == '\'' || file_line[q] == '-') {
					WordState = 1;
					next_word[fw_idx++] = file_line[q];
				}
			q++;
			}
			next_word[fw_idx] = '\0'; fw_idx = 0; q++;
			if(word_Comp(next_word, keyword[1]) == 0 && k_i == 2){
				flag = 1;
				check = 1;
				i = q;
			}
			if(k_i > 2 && word_Comp(next_word, keyword[1])==0){
				
			while(1){
				if (file_line[q] == ' ' || file_line[q] == '\0') {
					if (WordState == 1) {
						WordState = 0;
						break;
					}
				}
				else if ((file_line[q] >= 'A' && file_line[q] <= 'Z') || (file_line[q] >= 'a' && file_line[q] <= 'z') || file_line[q] == '\'' || file_line[q] == '-') {
					WordState = 1;
					next_word2[fw_idx++] = file_line[q];
				}
			q++;
			}
			next_word2[fw_idx] = '\0'; fw_idx = 0; q++;
			if(word_Comp(next_word2, keyword[2]) == 0 && k_i == 3){
				flag = 1;
				check = 1;
				i = q;
			}
			if(k_i > 3 && word_Comp(next_word2, keyword[2])==0){
				
			while(1){
				if (file_line[q] == ' ' || file_line[q] == '\0') {
					if (WordState == 1) {
						WordState = 0;
						break;
					}
				}
				else if ((file_line[q] >= 'A' && file_line[q] <= 'Z') || (file_line[q] >= 'a' && file_line[q] <= 'z') || file_line[q] == '\'' || file_line[q] == '-') {
					WordState = 1;
					next_word3[fw_idx++] = file_line[q];
				}
			q++;
			}
			next_word3[fw_idx] = '\0'; fw_idx = 0; q++;
			if(word_Comp(next_word3, keyword[3]) == 0  && k_i == 4){
				flag = 1;
				check = 1;
				i = q;
			}
			if(k_i > 4 && word_Comp(next_word3, keyword[3])==0){
				
			while(1){
				if (file_line[q] == ' ' || file_line[q] == '\0') {
					if (WordState == 1) {
						WordState = 0;
						break;
					}
				}
				else if ((file_line[q] >= 'A' && file_line[q] <= 'Z') || (file_line[q] >= 'a' && file_line[q] <= 'z') || file_line[q] == '\'' || file_line[q] == '-') {
					WordState = 1;
					next_word4[fw_idx++] = file_line[q];
				}
			q++;
			}
			next_word4[fw_idx] = '\0'; fw_idx = 0; q++;
			if(word_Comp(next_word4, keyword[4]) == 0 && k_i == 5){
				flag = 1;
				check = 1;
				i = q;
			}
			if(k_i > 5 && word_Comp(next_word4, keyword[4])==0){
				
			while(1){
				if (file_line[q] == ' ' || file_line[q] == '\0') {
					if (WordState == 1) {
						WordState = 0;
						break;
					}
				}
				else if ((file_line[q] >= 'A' && file_line[q] <= 'Z') || (file_line[q] >= 'a' && file_line[q] <= 'z') || file_line[q] == '\'' || file_line[q] == '-') {
					WordState = 1;
					next_word5[fw_idx++] = file_line[q];
				}
			q++;
			}
			next_word5[fw_idx] = '\0'; fw_idx = 0; q++;
			if(word_Comp(next_word5, keyword[5]) == 0 && k_i == 6){
				flag = 1;
				check = 1;
				i = q;
			}
			if(k_i > 6 && word_Comp(next_word5, keyword[5])==0){
				
			while(1){
				if (file_line[q] == ' ' || file_line[q] == '\0') {
					if (WordState == 1) {
						WordState = 0;
						break;
					}
				}
				else if ((file_line[q] >= 'A' && file_line[q] <= 'Z') || (file_line[q] >= 'a' && file_line[q] <= 'z') || file_line[q] == '\'' || file_line[q] == '-') {
					WordState = 1;
					next_word6[fw_idx++] = file_line[q];
				}
			q++;
			}
			next_word6[fw_idx] = '\0'; fw_idx = 0; q++;
			if(word_Comp(next_word6, keyword[6]) == 0 && k_i == 7){
				flag = 1;
				check = 1;
				i = q;
			}
			if(k_i > 7 && word_Comp(next_word6, keyword[6])==0){
				
			while(1){
				if (file_line[q] == ' ' || file_line[q] == '\0') {
					if (WordState == 1) {
						WordState = 0;
						break;
					}
				}
				else if ((file_line[q] >= 'A' && file_line[q] <= 'Z') || (file_line[q] >= 'a' && file_line[q] <= 'z') || file_line[q] == '\'' || file_line[q] == '-') {
					WordState = 1;
					next_word7[fw_idx++] = file_line[q];
				}
			q++;
			}
			next_word7[fw_idx] = '\0'; fw_idx = 0; q++;
			if(word_Comp(next_word7, keyword[7]) == 0 && k_i == 8){
				flag = 1;
				check = 1;
				i = q;
			}
			if(k_i > 8 && word_Comp(next_word7, keyword[7])==0){
				
			while(1){
				if (file_line[q] == ' ' || file_line[q] == '\0') {
					if (WordState == 1) {
						WordState = 0;
						break;
					}
				}
				else if ((file_line[q] >= 'A' && file_line[q] <= 'Z') || (file_line[q] >= 'a' && file_line[q] <= 'z') || file_line[q] == '\'' || file_line[q] == '-') {
					WordState = 1;
					next_word8[fw_idx++] = file_line[q];
				}
			q++;
			}
			next_word8[fw_idx] = '\0'; fw_idx = 0; q++;
			if(word_Comp(next_word8, keyword[8]) == 0 && k_i == 9){
				flag = 1;
				check = 1;
				i = q;
			}
			if(k_i > 9 && word_Comp(next_word8, keyword[8])==0){
				
			while(1){
				if (file_line[q] == ' ' || file_line[q] == '\0') {
					if (WordState == 1) {
						WordState = 0;
						break;
					}
				}
				else if ((file_line[q] >= 'A' && file_line[q] <= 'Z') || (file_line[q] >= 'a' && file_line[q] <= 'z') || file_line[q] == '\'' || file_line[q] == '-') {
					WordState = 1;
					next_word9[fw_idx++] = file_line[q];
				}
			q++;
			}
			next_word9[fw_idx] = '\0'; fw_idx = 0; q++;
			if(word_Comp(next_word9, keyword[9]) == 0 && k_i == 10){
				flag = 1;
				check = 1;
				i = q;
			}
			}
			}
			}
			}
			}
			}
			}
			}
		}
		

		if(flag == 0){ //키워드와 다른 단어일 경우
			for(int k = p; k < i; k++)
				res[idx++] = file_line[k];
		}	
		else{ // 키워드와 같은 단어일 경우
			if(k_i == 1){
			res[idx++] = '[';
			for(int k = 0; file_word[k] != '\0'; k++){
				res[idx++] = file_word[k];
			}
			res[idx++] = ']';
			res[idx++] = ' ';
			}
			if(k_i == 2){
			res[idx++] = '[';
			for(int k = 0; file_word[k] != '\0'; k++){
				res[idx++] = file_word[k];
			}
			res[idx++] = ' ';
			for(int k = 0; next_word[k] != '\0'; k++){
				res[idx++] = next_word[k];
			}
			res[idx++] = ']';
			res[idx++] = ' ';
			}
			if(k_i == 3){
			res[idx++] = '[';
			for(int k = 0; file_word[k] != '\0'; k++){
				res[idx++] = file_word[k];
			}
			res[idx++] = ' ';
			for(int k = 0; next_word[k] != '\0'; k++){
				res[idx++] = next_word[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word2[k] != '\0'; k++){
				res[idx++] = next_word2[k];
			}
			res[idx++] = ']';
			res[idx++] = ' ';
			}
			if(k_i == 4){
			res[idx++] = '[';
			for(int k = 0; file_word[k] != '\0'; k++){
				res[idx++] = file_word[k];
			}
			res[idx++] = ' ';
			for(int k = 0; next_word[k] != '\0'; k++){
				res[idx++] = next_word[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word2[k] != '\0'; k++){
				res[idx++] = next_word2[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word3[k] != '\0'; k++){
				res[idx++] = next_word3[k];
			}
			res[idx++] = ']';
			res[idx++] = ' ';
			}
			if(k_i == 5){
			res[idx++] = '[';
			for(int k = 0; file_word[k] != '\0'; k++){
				res[idx++] = file_word[k];
			}
			res[idx++] = ' ';
			for(int k = 0; next_word[k] != '\0'; k++){
				res[idx++] = next_word[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word2[k] != '\0'; k++){
				res[idx++] = next_word2[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word3[k] != '\0'; k++){
				res[idx++] = next_word3[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word4[k] != '\0'; k++){
				res[idx++] = next_word4[k];
			}
			res[idx++] = ']';
			res[idx++] = ' ';
			}
			if(k_i == 6){
			res[idx++] = '[';
			for(int k = 0; file_word[k] != '\0'; k++){
				res[idx++] = file_word[k];
			}
			res[idx++] = ' ';
			for(int k = 0; next_word[k] != '\0'; k++){
				res[idx++] = next_word[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word2[k] != '\0'; k++){
				res[idx++] = next_word2[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word3[k] != '\0'; k++){
				res[idx++] = next_word3[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word4[k] != '\0'; k++){
				res[idx++] = next_word4[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word5[k] != '\0'; k++){
				res[idx++] = next_word5[k];
			}
			res[idx++] = ']';
			res[idx++] = ' ';
			}
			if(k_i == 7){
			res[idx++] = '[';
			for(int k = 0; file_word[k] != '\0'; k++){
				res[idx++] = file_word[k];
			}
			res[idx++] = ' ';
			for(int k = 0; next_word[k] != '\0'; k++){
				res[idx++] = next_word[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word2[k] != '\0'; k++){
				res[idx++] = next_word2[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word3[k] != '\0'; k++){
				res[idx++] = next_word3[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word4[k] != '\0'; k++){
				res[idx++] = next_word4[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word5[k] != '\0'; k++){
				res[idx++] = next_word5[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word6[k] != '\0'; k++){
				res[idx++] = next_word6[k];
			}
			res[idx++] = ']';
			res[idx++] = ' ';
			}
			if(k_i == 8){
			res[idx++] = '[';
			for(int k = 0; file_word[k] != '\0'; k++){
				res[idx++] = file_word[k];
			}
			res[idx++] = ' ';
			for(int k = 0; next_word[k] != '\0'; k++){
				res[idx++] = next_word[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word2[k] != '\0'; k++){
				res[idx++] = next_word2[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word3[k] != '\0'; k++){
				res[idx++] = next_word3[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word4[k] != '\0'; k++){
				res[idx++] = next_word4[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word5[k] != '\0'; k++){
				res[idx++] = next_word5[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word6[k] != '\0'; k++){
				res[idx++] = next_word6[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word7[k] != '\0'; k++){
				res[idx++] = next_word7[k];
			}
			res[idx++] = ']';
			res[idx++] = ' ';
			}
			if(k_i == 9){
			res[idx++] = '[';
			for(int k = 0; file_word[k] != '\0'; k++){
				res[idx++] = file_word[k];
			}
			res[idx++] = ' ';
			for(int k = 0; next_word[k] != '\0'; k++){
				res[idx++] = next_word[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word2[k] != '\0'; k++){
				res[idx++] = next_word2[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word3[k] != '\0'; k++){
				res[idx++] = next_word3[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word4[k] != '\0'; k++){
				res[idx++] = next_word4[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word5[k] != '\0'; k++){
				res[idx++] = next_word5[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word6[k] != '\0'; k++){
				res[idx++] = next_word6[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word7[k] != '\0'; k++){
				res[idx++] = next_word7[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word8[k] != '\0'; k++){
				res[idx++] = next_word8[k];
			}
			res[idx++] = ']';
			res[idx++] = ' ';
			}
			if(k_i == 10){
			res[idx++] = '[';
			for(int k = 0; file_word[k] != '\0'; k++){
				res[idx++] = file_word[k];
			}
			res[idx++] = ' ';
			for(int k = 0; next_word[k] != '\0'; k++){
				res[idx++] = next_word[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word2[k] != '\0'; k++){
				res[idx++] = next_word2[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word3[k] != '\0'; k++){
				res[idx++] = next_word3[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word4[k] != '\0'; k++){
				res[idx++] = next_word4[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word5[k] != '\0'; k++){
				res[idx++] = next_word5[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word6[k] != '\0'; k++){
				res[idx++] = next_word6[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word7[k] != '\0'; k++){
				res[idx++] = next_word7[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word8[k] != '\0'; k++){
				res[idx++] = next_word8[k];
			}
			res[idx++] = ' ';
			for(int k = 0;next_word9[k] != '\0'; k++){
				res[idx++] = next_word9[k];
			}
			res[idx++] = ']';
			res[idx++] = ' ';
			}
		}
	}
	res[idx-1] = '\0';
	if(check == 0){
		res[0] = '0'; res[1] = '\0';
	}
	return res;
}

void CASE2(char* ReturnPhrase, ReadByLine file_Line, char *search_idx, char(*keyword)[30], int k_i, char* file_Name){
	int i = 0, k = 0, s = 0; int start = 0; char ret[500]; int flag = 0;
		char temp[10]; char fileIdx_temp[10];
		for(int i = 0; i < file_Line.line_Num; i++){
			if ((file_Line.line[i][0] >= '0' && file_Line.line[i][0] <= '9') || file_Line.line[i][0] == ' ') break;
			else start++;
			// 1장1절이 나올 때까지 패스
		}
				
		while (i < strlen(search_idx)) { // 찾을 단어 장절 저장
			while (1) {
				if (search_idx[i] == ' ' || search_idx[i] == '\0') break;
				temp[k++] = search_idx[i];
				i++;
			}
			temp[k] = '\0'; k = 0;
			for (int j = start; j < file_Line.line_Num; j++) {
				while (1) { // 장:절: 까지 읽고 반환
					if (file_Line.line[j][s] == ' ') break;
					fileIdx_temp[k++] = file_Line.line[j][s];
					s++;
				}
				fileIdx_temp[k] = '\0'; k = 0; s = 0;
				if (strcmp(temp, fileIdx_temp) == 0) {
					strcpy(ret, CASE2_bracket(keyword, file_Line.line[j], k_i));
					if(ret[0] == '0')
						break;
					else{	
						flag = 1;
						for(int p = 0; p < strlen(file_Name);p++){
							ReturnPhrase[l++] = file_Name[p];
						}
						while (ret[s] != '\0') {
							ReturnPhrase[l++] = ret[s];
							s++;
						}
						ReturnPhrase[l++] = '\n';
						break;
					}
				}
			}
			i++;
		}
		if(flag == 0){
			char tmp_str[20];
			for(int k = 0; k < strlen(file_Name)-1;k++)
				ReturnPhrase[l++] = file_Name[k];
			strcpy(tmp_str, " : Not found");
			for(int k = 0; k < strlen(tmp_str); k++)
				ReturnPhrase[l++] = tmp_str[k];
			ReturnPhrase[l++] = '\n';
		}	
}

char* CASE3_bracket(char (*keyword)[30], char *file_line, int k_i){
	char *res = (char*)malloc(sizeof(char)*500); int idx = 0; int i = 0; char file_word[30]; int fw_idx; int flag = 0;
	int WordState = 0; int p = 0, q = 0; char next_word[30]; int temp1; int temp2 = 0; int check = 0;
	while(1){ // 장:절 부분 입력
		if(file_line[i] == ' ') break;
		res[idx++] = file_line[i];
		i++;
	}
	res[idx++] = file_line[i++];
	//file_line을 word별로 읽으며 keyword와 비교
	while(i<strlen(file_line)){
		p = i; temp1 = i;
		flag = 0;
		while(1){
		if (file_line[i] == ' ' || file_line[i] == '\0') {
			if (WordState == 1) {
				WordState = 0;
				break;
			}
		}
		else if ((file_line[i] >= 'A' && file_line[i] <= 'Z') || (file_line[i] >= 'a' && file_line[i] <= 'z') || file_line[i] == '\'' || file_line[i] == '-') {
			WordState = 1;
			file_word[fw_idx++] = file_line[i];
		}
		i++;
		}
		file_word[fw_idx] = '\0'; fw_idx = 0; i++;
		//첫 번째 키워드와 같은 단어를 찾으면
		if(word_Comp(file_word, keyword[0]) == 0){
			//다음 키워드 단어가 나올 때까지
			q = i;
			while(q < strlen(file_line)){
				while(1){
					if (file_line[q] == ' ' || file_line[q] == '\0') {
						if (WordState == 1) {
							WordState = 0;
							break;
						}
					}
					else if ((file_line[q] >= 'A' && file_line[q] <= 'Z') || (file_line[q] >= 'a' && file_line[q] <= 'z') || file_line[q] == '\'' || file_line[q] == '-') {
						WordState = 1;
						next_word[fw_idx++] = file_line[q];
					}
				q++;
				}
				next_word[fw_idx] = '\0'; fw_idx = 0; q++;
				if(word_Comp(next_word, keyword[1]) == 0) break;
			}
			if(word_Comp(next_word, keyword[1])==0){
				flag = 1;
				check = 1;
				i = q;
			}
		}

		if(flag == 0){ //키워드와 다른 단어일 경우
			for(int k = p; k < i; k++)
				res[idx++] = file_line[k];
		}	
		else{ // 키워드와 같은 단어일 경우
			for(int k = i - 1; file_line[k] <= 'a' || file_line[k] >= 'z'; k--)
				temp2 = k;
			res[idx++] = '[';
			for(int k = temp1; k<temp2; k++){
				res[idx++] = file_line[k];
			}
			res[idx++] = ']';
			for(int k = temp2;k<i;k++){
				res[idx++] = file_line[k];
			}
		}
	}
	res[idx-1] = '\0';
	if(check == 0){
		res[0] = '0'; res[1] = '\0';
	}
	return res;
}

void CASE3(char* ReturnPhrase, ReadByLine file_Line, char *search_idx, char(*keyword)[30], int k_i, char* file_Name){
	int i = 0, k = 0, s = 0; int start = 0; char ret[500]; int flag = 0;
		char temp[10]; char fileIdx_temp[10];
		for(int i = 0; i < file_Line.line_Num; i++){
			if ((file_Line.line[i][0] >= '0' && file_Line.line[i][0] <= '9') || file_Line.line[i][0] == ' ') break;
			else start++;
			// 1장1절이 나올 때까지 패스
		}
				
		while (i < strlen(search_idx)) { // 찾을 단어 장절 저장
			while (1) {
				if (search_idx[i] == ' ' || search_idx[i] == '\0') break;
				temp[k++] = search_idx[i];
				i++;
			}
			temp[k] = '\0'; k = 0;
			for (int j = start; j < file_Line.line_Num; j++) {
				while (1) { // 장:절: 까지 읽고 반환
					if (file_Line.line[j][s] == ' ') break;
					fileIdx_temp[k++] = file_Line.line[j][s];
					s++;
				}
				fileIdx_temp[k] = '\0'; k = 0; s = 0;
				if (strcmp(temp, fileIdx_temp) == 0) {
					strcpy(ret, CASE3_bracket(keyword, file_Line.line[j], k_i));
					if(ret[0] == '0')
						break;
					else{
						flag = 1;
						for(int p = 0; p < strlen(file_Name);p++){
							ReturnPhrase[l++] = file_Name[p];
						}
						while (ret[s] != '\0') {
							ReturnPhrase[l++] = ret[s];
							s++;
						}
						ReturnPhrase[l++] = '\n';
						break;
					}
				}
			}
			i++;
		}
		if(flag == 0){
			char tmp_str[20];
			for(int k = 0; k < strlen(file_Name)-1;k++)
				ReturnPhrase[l++] = file_Name[k];
			strcpy(tmp_str, " : Not found");
			for(int k = 0; k < strlen(tmp_str); k++)
				ReturnPhrase[l++] = tmp_str[k];
			ReturnPhrase[l++] = '\n';
		}
}


ReadByLine readLine(int fd) { // 파일을 라인별로 읽어 저장
	ReadByLine temp;
	char *lineBuf;
	int lineBufSize;
	int lineBufLimit = 500;
	int lineArrLimit = 500;
	char buf[MAX_BUF_LIMIT + 1];
	int size;

	lineBuf = (char*)malloc(lineBufLimit * sizeof(char));
	lineBufSize = 0;

	temp.line = (char**)malloc(lineArrLimit * sizeof(char*));
	temp.line_Num = 0;

	size = read(fd, buf, MAX_BUF_LIMIT);

	for (int i = 0; i < size; i++) {
		if (buf[i] == '\0')
			break;

		if (buf[i] == '\n') {

			if (temp.line_Num == lineArrLimit) {
				lineArrLimit += 100;
				temp.line = (char**)realloc(temp.line, lineArrLimit * sizeof(char*));
			}

			temp.line[temp.line_Num] = (char*)malloc(lineBufSize * sizeof(char) + 1);

			for (int j = 0; j < lineBufSize; j++)
				temp.line[temp.line_Num][j] = lineBuf[j];
			temp.line[temp.line_Num][lineBufSize] = '\0';
			lineBufSize = 0;
			temp.line_Num++;
			continue;
		}

		if (lineBufSize == lineBufLimit) {
			lineBufLimit += 100;
			lineBuf = (char*)realloc(lineBuf, lineBufLimit * sizeof(char));
		}
		lineBuf[lineBufSize++] = buf[i];
	}
	return temp;
}

void SearchPhrase(char* ReturnPhrase, char* buf, int len) {
	buf[len-1] = '\0'; l = 0;
	int fd_bible, fd_index, fd_file; ReadByLine bible_Line; ReadByLine file_Line; ReadByLine index_Line;
	char file_Name[20]; char index_Name[20]; char file_title[20];
	char keyword[10][30];  int word_count[10] = {0,}; char temp_count[30]; int x = 0;
	char search_idx1[300000]; char search_idx[10][300000]; char search_word[30]; 
	int i=0, j=0, m=0, s=0, k =0, n=0, p=0, idx_num=0, temp = 0, k_i = 0; int case_flag = 0; int tmp = 0;
	char index_word[30]; // index 파일에 있는 단어를 저장 후 비교를 위한 변수
	int search_index = -1; // 찾을 단어가 있는 index파일에서의 줄 위치
	char idx_comp1[10]; char idx_comp2[10]; // 찾을 단어들이 같이 포함되어 있는 절을 찾을 때 비교를 위한 변수
	fd_bible = open("bible.txt", O_RDONLY);
	bible_Line = readLine(fd_bible);

	//단어 저장
	//by case
	if(buf[0] ==  '\"'){
		case_flag = 1;
		while(i<len-1){
			if(buf[i] == '*') {
				case_flag = 2;
				break;
			}
			i++;
		}
		i = 1;
		if(case_flag == 1){ // 연속된 단어의 검색이면
			while(i < len - 1){
				s = 0;
				while(1) {
					if(buf[i] == ' ' || buf[i] == '\"') break;
					search_word[s] = buf[i];
					i++; s++;
				}
				search_word[s] = '\0'; i++;
				strcpy(keyword[k_i], search_word); k_i++;
			}
		}
		else { //시작과 끝 단어의 검색이면
			while(i < len - 1){
				s = 0;
				while(1) {
					if(buf[i] == '*' || buf[i] == '\"') break;
					if(buf[i] != ' '){
						search_word[s] = buf[i]; s++;
					}	
					i++;
				}
				search_word[s] = '\0'; i++;
				strcpy(keyword[k_i], search_word); k_i++;
			}
		}
	}
	else{	
		while(i < len -1){
			s = 0;
			while (1) {
				if (buf[i] == ' ' || buf[i] == '\0') break;
				search_word[s] = buf[i];
				i++; s++;
			}
		search_word[s] = '\0'; i++; // 한 단어 저장
		strcpy(keyword[k_i], search_word); k_i++; //입력 단어를 모두 저장
		}
	}
	i = 0;
	
	//bible.txt를 라인별로 읽어서 파일 이름과 인덱스 파일 이름을 저장
	for (int b = 0; b < bible_Line.line_Num; b++) {
		j = 0, m = 0;
		while (bible_Line.line[b][j] != ' ') { //파일 이름까지 저장
			file_Name[j] = bible_Line.line[b][j];
			j++;
		}
		file_Name[j++] = '\0';
		while (bible_Line.line[b][j] != '\0') { //파일 인덱스 저장
			index_Name[m] = bible_Line.line[b][j];
			j++; m++;
		}
		index_Name[m] = '\0';
		//장 앞에 붙을 파일명 자르기
		for(int k = 0; file_Name[k] != '.';k++)
			file_title[tmp++] = file_Name[k];
		file_title[tmp++] = ':';
		file_title[tmp] = '\0'; tmp = 0;
		fd_file = open(file_Name, O_RDONLY);
		fd_index = open(index_Name, O_RDONLY);

		file_Line = readLine(fd_file); //파일 라인별 저장
		index_Line = readLine(fd_index); // 인덱스 라인별 저장
		idx_num = 0;
		while (i < k_i) {
			search_index = -1;
				//search_word에 저장된 단어를 fd_index에서 searching
				 //index 파일을 읽으면서 찾을 단어의 인덱스를 찾음
			for (int k = 0; k < index_Line.line_Num; k++) {
				for (temp = 0; index_Line.line[k][temp] != ':'; temp++) {
					index_word[temp] = index_Line.line[k][temp];
				}
				index_word[temp] = '\0'; //index 파일 단어를 저장
				if (strcmp(index_word, keyword[i]) == 0) {
					search_index = k;
					break;
				}
			}
			if(search_index == -1){
				char tmp_str[20];
				for(int k = 0; k < strlen(file_title)-1;k++)
					ReturnPhrase[l++] = file_title[k];
				strcpy(tmp_str, " : Not found");
				for(int k = 0; k < strlen(tmp_str); k++)
					ReturnPhrase[l++] = tmp_str[k];
				ReturnPhrase[l++] = '\n';
				ReturnPhrase[l++] = '\n';
				ReturnPhrase[l] = '\0';
				return;
			};	
			for(n = 0; index_Line.line[search_index][n] != ' '; n++); n++;
			while(index_Line.line[search_index][n] != ' '){
				temp_count[x++] = index_Line.line[search_index][n];
				n++;
			}
			temp_count[x] = '\0'; x=0;
			word_count[i] = atoi(temp_count);	
			//단어의 인덱스가 저장된 시작 지점 찾기
			for (n = 0; index_Line.line[search_index][n] != ' '; n++);
			n++;
			while (index_Line.line[search_index][n] != ' ') {
				n++;
			}
			n++;
			//search_idx1에 단어의 "장:절:"을 모두 저장
			while (1) {
				while (index_Line.line[search_index][n] != ':') {
					search_idx1[p] = index_Line.line[search_index][n];
					p++; n++;
				}
				search_idx1[p++] = index_Line.line[search_index][n]; n++;
				while (index_Line.line[search_index][n] != ':') {
					search_idx1[p] = index_Line.line[search_index][n];
					p++; n++;
				}
				search_idx1[p++] = index_Line.line[search_index][n]; n++;
				while (1) {
					if (index_Line.line[search_index][n] == ' ' || index_Line.line[search_index][n] == '\0') break;
					n++;
				}
				//while (index_Line.line[search_index][n] != ' ' || index_Line.line[search_index][n] != '\0') {
				//	n++;
				//}
				if (index_Line.line[search_index][n] == ' ') {
					n++;
					search_idx1[p++] = ' ';
				}
				else if (index_Line.line[search_index][n] == '\0') {
					search_idx1[p] = '\0';
					p = 0;
					break;
				}
			}
			strcpy(search_idx[idx_num++], search_idx1); // 단어가 있는 장절 내용을 저장
			i++; // 다음 단어 찾기
		}
		// client로부터 받은 단어들의 장:절: 을 찾았다면
		// 받은 단어 개수가 2개 이상일 경우, 두 단어가 같이 포함되어 있는 장:절: 을 찾아야 한다.
		i = 0; k = 0; s = 0; n = 0; p = 0; int c = 0;  //변수 재활용
		int min = c;
		for(c = 0;c<k_i;c++){
			if(word_count[min] > word_count[c])
				min = c;
		}
		char temp_ch[300000];
		strcpy(temp_ch, search_idx[min]);
		strcpy(search_idx[min], search_idx[0]);
		strcpy(search_idx[0], temp_ch);
		char temp_idx[10000]; char temp_comp[10] = { '0', };
		if (idx_num > 1) {
			while (n < idx_num - 1) {
				while (i < strlen(search_idx[n])) {
					while (1) {
						if (search_idx[n][i] == ' ' || search_idx[n][i] == '\0') break;
						idx_comp1[k++] = search_idx[n][i];
						i++;
					}
					idx_comp1[k] = '\0'; k = 0; i++;
					if (strcmp(temp_comp, idx_comp1) == 0) {
						continue;
					}
					strcpy(temp_comp, idx_comp1);
					while (s < strlen(search_idx[n + 1])) {
						while (1) {
							if (search_idx[n + 1][s] == ' ' || search_idx[n + 1][s] == '\0') break;
							idx_comp2[k++] = search_idx[n + 1][s];
							s++;
						}
						idx_comp2[k] = '\0'; k = 0; s++;
						if (strcmp(idx_comp1, idx_comp2) == 0) break;
					}
					if (strcmp(idx_comp1, idx_comp2) == 0) {
						for (int i = 0; i < strlen(idx_comp1); i++) {
							temp_idx[p++] = idx_comp1[i];
						}
						temp_idx[p++] = ' ';
					}
					s = 0;
				}
				temp_idx[p - 1] = '\0';
				strcpy(search_idx[n + 1], temp_idx);
				p = 0; i = 0;
				n++;
			}
		}
		else {
			while (i < strlen(search_idx[n])) {
				while (1) {
					if (search_idx[n][i] == ' ' || search_idx[n][i] == '\0') break;
					idx_comp1[k++] = search_idx[n][i];
					i++;
				}
				idx_comp1[k] = '\0'; k = 0; i++;
				if (strcmp(temp_comp, idx_comp1) == 0) {
					continue;
				}
				strcpy(temp_comp, idx_comp1);
				for(int k = 0; k < strlen(idx_comp1); k++){
					temp_idx[p++] = idx_comp1[k];
				}
				temp_idx[p++] = ' ';
			}
			temp_idx[p-1] = '\0';
			strcpy(search_idx[n], temp_idx);
		}

		//search_idx[idx_num]에 단어들이 같이 포함되어있는 장:절: 이 저장됨
		//fd_file에서 search_idx에 있는 장절들의 내용을 찾아 ReturnPhrase에 저장
		//case1 : 여러 단어 찾기
		//case2 : 연속된 단어 찾기
		//case3 : 시작 끝 단어 찾기
		if(case_flag == 0)
			CASE1(ReturnPhrase, file_Line, search_idx[idx_num - 1], keyword, k_i, file_title);
		else if(case_flag == 1)
			CASE2(ReturnPhrase, file_Line, search_idx[idx_num - 1], keyword, k_i, file_title);
		else if(case_flag == 2)
			CASE3(ReturnPhrase, file_Line, search_idx[idx_num - 1], keyword, k_i, file_title);

		close(fd_file);
		close(fd_index);
		i = 0; k = 0, s = 0; n = 0; p = 0;
	}
	close(fd_bible);
	ReturnPhrase[l++] = '\n';
	ReturnPhrase[l] = '\0';
}

void *thread(void *vargp);

struct sockaddr_in clientaddr, saddr;

int main(int argc, char **argv)
{
	int listenfd, port;
	int* connfdp;
	socklen_t clientlen = sizeof(struct sockaddr_in);
	pthread_t tid;
	int errno;
	if(argc!=2)
	{
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(0);
	}

	port = atoi(argv[1]);
	//socket creation
	if((listenfd = socket(AF_INET, SOCK_STREAM, 0))<0)
	{
		printf("socket() failed.\n");
		exit(1);
	}

	bzero((char *)&saddr, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = htons(port);

	//bind
	if(bind(listenfd, (struct sockaddr *)&saddr,  sizeof(saddr))<0)
	{
		printf("bind() failed.\n");
		exit(2);
	}

	//listen
	if(listen(listenfd, 5)<0)
	{
		printf("listen() failed.\n");
		exit(3);
	}
	int n_id; char buf_id[100];
	n_id = sprintf(buf_id, "\nStarted server: %d\n", port);
	errno = write(1, buf_id, n_id);


	while(1)
	{
		connfdp = (int*)malloc(sizeof(int));
		if((*connfdp = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen))>=0){
			 n_id = sprintf(buf_id, "Connected : %s\n", inet_ntoa(clientaddr.sin_addr));
			 errno = write(1, buf_id, n_id);
			 pthread_create(&tid, NULL, thread, connfdp);
		}
		else if(*connfdp < 0)
		{
			printf("accept() failed.\n");
			continue;
		}
	}
	n_id = errno;
}

void *thread(void *vargp)
{
	int connfd, n, n1, errno;
	char buf[GETSIZE];
	char buf1[GETSIZE];
	char ReturnPhrase[MAXSIZE];
	connfd = *((int*)vargp);
	pthread_detach(pthread_self());
	free(vargp);

	int word_Comp(char *arr1, char* arr2);
	char* CASE1_bracket(char (*keyword)[30], char *file_line, int k_i);
	void CASE1(char* ReturnPhrase, ReadByLine file_Line, char *search_idx, char(*keyword)[30], int k_i, char* file_Name);
	char* CASE2_bracket(char (*keyword)[30], char *file_line, int k_i);
	void CASE2(char* ReturnPhrase, ReadByLine file_Line, char *search_idx, char(*keyword)[30], int k_i, char* file_Name);
	char* CASE3_bracket(char (*keyword)[30], char *file_line, int k_i);
	void CASE3(char* ReturnPhrase, ReadByLine file_Line, char *search_idx, char(*keyword)[30], int k_i, char* file_Name);
	ReadByLine readLine(int fd);
	void SearchPhrase(char* ReturnPhrase, char* buf, int len);

		while((n=read(connfd, buf, GETSIZE)) > 0){
			buf[n-1] = '\0';
			n1 = sprintf(buf1, "search : %s\n", buf);
			errno = write(1, buf1, n1);
			SearchPhrase(ReturnPhrase, buf, n);
			n = write(connfd, ReturnPhrase, strlen(ReturnPhrase));
		}
		n1 = sprintf(buf1, "Disconnected : %s\n", inet_ntoa(clientaddr.sin_addr));
		errno = write(1, buf1, n1);
		n1 = errno;
		close(connfd);
	return NULL;
} 
