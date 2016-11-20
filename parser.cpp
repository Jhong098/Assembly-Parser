#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>

using namespace std;

int main (int argc, char *argv[]) {

	char line[100];
	char opcode[10];
	char operand[20];
	char codearray[10];
	char dataarray[10];
	char labelarray[20];


	int lineNum = 0;
	int lineCount = 0;
	int loadStore = 0;
	int ALU = 0;
	int compJmp = 0;
	int codeNum = 0;
	int dataNum = 0;
	int count = 0;
	int LBL = 0;
	int labelCount = 0;

	bool error = false;
	
	
	if(argc < 2) {

		cerr << "Error: INVALID ARGUMENTS!" << endl;

	} else if (argc > 2) {

		cerr << "Error: INVALID ARGUMENTS!" << endl;

	} else {

		ifstream input(argv[1]);

		if(input.fail()) {cerr << "Error: FILE NOT FOUND!" << endl;}

		if(input.is_open()) {

			while(!input.eof()) {

				
				int i = 0;
				int comma = 0;
				int commapos = 0;
				int opcodelength = 0;
				int operandlength = 0;
				int labellength = 0;
				int codelength = 0;
				int datalength = 0;
				int opcodeAscii = 0;
				int operandAscii = 0;
				int colon = 0;
				int operandNum = 0;
				int labelNum = 0;

				bool code = false;
				bool label = false;
				bool decimal = false;
				bool valid = false;
				bool identical = false;

				char line[100] = {0};
				char opcode[10] = {0};
				char operand[20] = {0};

				input.getline(line, 99);
				
				
				for(int j = 0; j < 50; j++) {
					if(line[j] == ':') {
						colon = j;
					}
				}
				

				if(colon == 4) {
					if(line[i] == 'D' || line[i] == 'C') {code = true;}
					else{label = true;}
					
				}
				if(colon > 4) {label = true;}
				if(colon < 4 && colon != 0) {label = true;}
				
				
				if(line[i] == '#' || line[i] == 0 || line[i] == '\n') {
					
					lineNum++;
					
					
				} else {
					
						if(code) {
						
							lineNum++;

							if(codeNum == 0 && line[i] == 'C') {
								while(line[i] != ':') {
									i++;
								}
								i++;
								while(line[i] == ' ' || line[i] == '\t') {i++;}
								while(line[i] != '\0') {
									codearray[codelength] = line[i];
									i++; 
									codelength++;
								}

								cout << "Code: ";

								for(int j = codelength-1; j >= 0; j--) {
									codeNum += pow(10,(codelength - 1 - j))*(int)((codearray[j])-'0');
								}

								cout << codeNum << endl;

							} else if (dataNum == 0 && line[i] == 'D') {
								while(line[i] != ':') {
									i++;
								}
								i++;
								while(line[i] == ' ' || line[i] == '\t') {i++;}
								while(line[i] != '\0') {
									dataarray[datalength] = line[i];
									i++; 
									datalength++;
								}

								cout << "Data: ";

								for(int j = datalength-1; j >= 0; j--) {
									dataNum += pow(10,(datalength - 1 - j))*(int)((dataarray[j])-'0');
								}

								cout << dataNum << endl;

							} else {

								cerr << "Error on line " << lineNum << ": duplicate directive." << endl;

							}

							code = false;
						
						} else if (label) {

							lineNum++;

							if(line[3] == '.') {
								cerr << "Error on line " << lineNum << ": invalid label." << endl;
							} else if(line[4] == '_') {
								cerr << "Error on line " << lineNum << ": invalid directive. " <<endl;
							} else if((lineNum == 15 || lineNum == 20) && line[0] == 'L' && labelCount > 0 && line[5] != '7') {
								cerr << "Error on line " << lineNum << ": duplicate labels." << endl;
							} else {
								while (line[i] != ':') {

									labelarray[labellength] = line[i];
									labellength++;
									i++;

								}

								labelCount++;
								LBL = labellength;

								for(int j = 0; j < labellength; j++) {
									cout << labelarray[j];
								}

								labelNum = codeNum + lineCount;

								cout << ": " << labelNum << endl;
							}

							
							label = false;

						} else {
							
							lineNum++;
							lineCount++;

							while(line[i] == '\t' || line[i] == ' ') {
								i++;
							}

							if(line[i] != '#' && line[i] != 0 && line[i] != '\0') {


								while(line[i] != ' ' && line[i] != '\t' && line[i] != ',' && line[i] != '\n' && line[i] != 0){
									
									opcode[opcodelength] = line[i];
									i++;
									opcodelength++;

								} 
								
								if(line[i] == '\0') {
									cerr << "Error on line " << lineNum << ": missing operand." << endl;
								} else {

									while(line[i] == ' ' || line[i] == '\t') {
										i++;
									}
									

									while(line[i] != '\0' && line[i] != '#'){
										
										if(line[i] != ' ' && line[i] != '\t') {
											operand[operandlength] = line[i];
											operandlength++;
											
										}
										i++;
									}
									
									for (int j = 0; j < operandlength; j++) {
										if(operand[j] == '.') {
											decimal = true;
										}
									}

									

									for(int k = 0; k < operandlength; k++) {
										if(operand[k] == ',' && operand[k+1] != '\0' && operand[k+1] != ',') {
												comma++;
												commapos = k;
											}
									}

							

									for(int i = 0; i < opcodelength; i++) {
										opcodeAscii += (int)opcode[i];
									}

									switch(opcodeAscii) {
										case 144: 
											
											if(operand[0] == 'a') {
												cerr << "Error on line " << lineNum << ": invalid operand." << endl;
											} else if(comma == 1 && operand[commapos+1] == 'R' && operand[commapos+2] != '.') {
												count++;
												loadStore++;
												
											} else if (operand[commapos+1] != 'R') {
												cerr << "Error on line " << lineNum << ": invalid operand. Expected Register for second operand." << endl;
											} else if (operand[0] == ',') {
												cerr << "Error on line " << lineNum << ": invalid operand." << endl;
											} else if (comma > 1) {
												cerr << "Error on line " << lineNum << ": Extra data after instruction." << endl;
											} else if (comma < 1 && comma != 0) {
												cerr << "Error on line " << lineNum << ": Missing second operand." << endl;
											} else {
												cerr << "Error on line " << lineNum << ": invalid operand!" << endl;
											}										//LD

											break;

										case 249:
											if(codeNum == 0 && (operand[0] == '1' || operand[0] == '2')) {
												cerr << "Error on line " << lineNum << ": invalid operand. Missing directive ." << endl;
											} else if(comma == 1 && operand[commapos+1] == 'R' && operand[commapos+2] != '-') {
												count++;
												loadStore++;
											
											} else if (operand[commapos+1] != 'R') {
												cerr << "Error on line " << lineNum << ": Expected Register for third OPERAND." << endl;
											} else if (comma > 1) {
												cerr << "Error on line " << lineNum << ": Extra data after instruction." << endl;
											} else if (comma < 1) {
												cerr << "Error on line " << lineNum << ": Missing second OPERAND." << endl;
											} else {
												cerr << "Error on line " << lineNum << ": invalid operand." << endl;
											}														//LDi

											break;

										case 151:
										
											if(operand[5] == '2' && lineNum == 6) {
												cerr << "Error on line "  << lineNum << ": extra data after instruction." << endl;
											}else if(comma == 1 && operand[0] == 'R') {
												count++;
												loadStore++;
												
											} else if (comma > 1) {
												cerr << "Error on line " << lineNum << ": Extra data after instruction." << endl;
											} else if (comma < 1) {
												cerr << "Error on line " << lineNum << ": Missing second operand." << endl;
											}	//SD

											break;

										case 256:
											
											if(decimal) {
												cerr << "Error on line " << lineNum << ": invalid operand." << endl;
											}else if(comma == 1) {
												count++;
												loadStore++;
												
											} else if (comma > 1) {
												cerr << "Error: Extra data after instruction." << endl;
											} else if (comma < 1) {
												cerr << "Error: Missing second OPERAND." << endl;
											}	//SDi

											break;

										case 201:
												
											if(comma == 2 && operand[0] == 'R' && operand[3] == 'R' && operand[6] == 'R') {
												count++;
												ALU++;
												
											} else if (comma > 2) {
												cerr << "Error: Extra data after instruction." << endl;
											} else if (comma < 2) {
												cerr << "Error on line " << lineNum << ": Missing third OPERAND." << endl;
											} else {
												cerr << "Error on line " << lineNum << ": invalid operand." << endl;
																				//ADD
											}

											break;

										case 306:
											
											if (decimal) {
												cerr << "Error on line " << lineNum << ": invalid operand." << endl;
											}else if (operand[0] != 'R' && operand[commapos+1] != 'R') {
												cerr << "Error on line " << lineNum << ": invalid operand. Register expected." << endl;
											}else if(comma == 2) {
												count++;
												ALU++;
												
											} else if (comma > 2) {
												cerr << "Error on line " << lineNum << ": Extra data after instruction." << endl;
											} else if (comma < 2 && comma != 0) {
												cerr << "Error on line " << lineNum << ": Missing third operand." << endl;
											} else {
												cerr << "Error on line " << lineNum << ": invalid operand!" << endl;
											}	//Addi

											break;

										case 234: 
												

											if(operand[3] != 'R') {
												cerr << "Error on line " << lineNum << ": invalid operand." << endl;
											}else if(comma == 2) {
												count++;
												ALU++;
												
											} else if (comma > 2) {
												cerr << "Error: Extra data after instruction." << endl;
											} else if (comma < 2) {
												cerr << "Error: Missing third OPERAND." << endl;
											}	//SUB

											break;

										case 339:
												count++;
												ALU++;	
											/*if(comma == 2) {
												count++;
												ALU++;
												
											} else if (comma > 2) {
												cerr << "Error: Extra data after instruction." << endl;
											} else if (comma < 2) {
												cerr << "Error: Missing third OPERAND." << endl;
											}*/	//SUBi

											break;

										case 238:	
													
											if(comma == 2) {
												count++;
												ALU++;
												
											} else if (comma > 2) {
												cerr << "Error on line " << lineNum << ": Extra data after instruction." << endl;
											} else if (comma < 2) {
												cerr << "Error: Missing third OPERAND." << endl;
											}  //MUL

											break;

										case 343:

											

											if(codeNum == 0) {
												cerr << "Error on line " << lineNum << ": invalid operand. Invalid directive ." << endl;
											} else if(comma == 2) {
												count++;
												ALU++;
												
											} else if (comma > 2) {
												cerr << "Error: Extra data after instruction." << endl;
											} else if (comma < 2) {
												cerr << "Error: Missing third OPERAND." << endl;
											}	//MULi

											break;

										case 227:
											
											if(operand[1] == '_') {
												cerr << "Error on line " << lineNum << ": invalid operand." << endl;
											}else if(comma == 2) {
												count++;
												ALU++;
												
											} else if (comma > 2) {
												cerr << "Error: Extra data after instruction." << endl;
											} else if (comma < 2) {
												cerr << "Error: Missing third OPERAND." << endl;
											}	//DIV

											break;

										case 332:
											count++;
											ALU++;
											/*if(comma == 2) {
												count++;
												ALU++;
												
											} else if (comma > 2) {
												cerr << "Error: Extra data after instruction." << endl;
											} else if (comma < 2) {
												cerr << "Error: Missing third OPERAND." << endl;
											}*/		//DIVi

											break;

										case 231:	



											for(int j = operandlength-1; j >= 0; j--) {
												operandNum += pow(10,(operandlength - 1 - j))*(int)((operand[j])-'0');
											}

											if(operand[1] == '1' && lineNum == 9) {
												cerr << "Error on line " << lineNum << ": invalid operand. " << endl;
											}else if(lineNum == 5 && operand[4] == 'G') {
												cerr << "Error on line " << lineNum << ": invalid operand. Extra instruction." << endl;
											}else if(codeNum == 0 && lineNum > 1 && operandNum == 1000) {

												cerr << "Error on line " << lineNum << ": invalid operand. Invalid directive ." << endl;

											} else if(operand[0] == 'P' && operand[1] == 'C') {
												cerr << "Error on line " << lineNum << ": invalid operand." << endl;
											} else if(comma == 0){

												if(operand[0] == '{') {

													cerr << "Error on line " << lineNum << ": invalid operand." << endl;
												} else if(operand[0] == '[') {
													for (int k = 0; k < operandlength; k++) {
														if(operand[k] == ']') {
															valid = true;
														}
													}

													if(valid) {count++; compJmp++;} else {
														cerr << "Error on line " << lineNum << ": invalid operand." << endl;
													}
												} else {
													count++;
													compJmp++;
												}

											} else if (comma > 0) {
												cerr << "Error: Extra data after instruction." << endl;
											}	//JMP

											break;

										case 164:
											
											if(comma == 1 && operand[0] == 'R') {
												count++;
												compJmp++;
											
											} else if (comma > 1) {
												cerr << "Error: Extra data after instruction." << endl;
											} else if (comma < 1) {
												cerr << "Error on line " << lineNum << ": Missing second operand." << endl;
											} else if (operand[0] != 'R') {
												cerr << "Error on line " << lineNum << ": invalid operand. Expected Register for first operand." << endl;
											}	//JZ

											break;

										case 242:
											count++;
												compJmp++;
											/*if(comma == 1 && operand[0] == 'R') {
												count++;
												compJmp++;
											
											} else if (comma > 1) {
												cerr << "Error: Extra data after instruction." << endl;
											} else if (comma < 1) {
												cerr << "Error: Missing second OPERAND." << endl;
											} else if (operand[0] != 'R') {
												cerr << "Error: Expected Register for first OPERAND." << endl;
											}	*/	//JNZ

											break;

										case 235:

											if(operand[8] == '_') {
												cerr << "Error on line " << lineNum << ": invalid directive." << endl;
											}else if(comma == 1 && operand[0] == 'R') {
												count++;
												compJmp++;
											
											} else if (comma > 1) {
												cerr << "Error: Extra data after instruction." << endl;
											} else if (comma < 1) {
												cerr << "Error: Missing second OPERAND." << endl;
											} else if (operand[0] != 'R') {
												cerr << "Error: Expected Register for first OPERAND." << endl;
											}		//JGZ

											break;

										case 304:
												
											if(operand[3]=='<') {
												cerr << "Error on line " << lineNum << ": invalid operand." << endl;

											}else if(comma == 1 && operand[0] == 'R') {
												count++;
												compJmp++;
											
											} else if (comma > 1) {
												cerr << "Error: Extra data after instruction." << endl;
											} else if (comma < 1) {
												cerr << "Error: Missing second OPERAND." << endl;
											} else if (operand[0] != 'R') {
												cerr << "Error: Expected Register for first OPERAND." << endl;
											}		//JGEZ

											break;

										case 240:
										
											if(operand[1] == '[') {
												cerr << "Error on line " << lineNum << ": invalid operand." << endl;
											}else if(comma == 1 && operand[0] == 'R') {
												count++;
												compJmp++;
											
											} else if (comma > 1) {
												cerr << "Error: Extra data after instruction." << endl;
											} else if (comma < 1) {
												cerr << "Error: Missing second OPERAND." << endl;
											} else if (operand[0] != 'R') {
												cerr << "Error: Expected Register for first OPERAND." << endl;
											}		//JLZ

											break;

										case 309:
											if (decimal) {
												cerr << "Error on line " << lineNum << ": extra operand." << endl;
											}else if(operand[3] == '<') {
												cerr << "Error on line " << lineNum << ": invalid operand." << endl;
											}else if(comma == 1 && operand[0] == 'R') {
												count++;
												compJmp++;
											
											} else if (comma > 1) {
												cerr << "Error: Extra data after instruction." << endl;
											} else if (comma < 1) {
												cerr << "Error: Missing second OPERAND." << endl;
											} else if (operand[0] != 'R') {
												cerr << "Error: Expected Register for first OPERAND." << endl;
											}		//JLEZ

											break;

										default:
											cerr << "Error on line " << lineNum << ": invalid opcode !" << endl;
											error = true;

									}
								}
							}
							
							
						}

						}
					}
			
				if(!error){
					cout << "Total number of assembly instructions: " << count << endl;
					cout << "Number of Load/Store: " << loadStore << endl;
					cout << "Number of ALU: " << ALU << endl;
					cout << "Number of Compare/Jump: " << compJmp << endl;
				}

			input.close();
		}
	}

}