#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<fstream>
#include<memory.h>
#include<vector>
#include<string>
#define SIZE 32
#define INPUT "pipeline.in"
#define OUTPUT "pipeline.out"

using namespace std;



struct instruction
{
	int rs , rt , rd ;    //記暫存器的編號(不是值)
	int immediateOrLabel;
	int function ;        //1 = lw 
                          //2 = sw 
                          //3 = beq
                          //4 = add
                          //5 = sub

};

bool Struct1EStruct2( struct instruction a, struct instruction b)
{
	
	      
	 if(    a.function==b.function
		 && a.immediateOrLabel==b.immediateOrLabel
	     && a.rs==b.rs
	     && a.rt==b.rt
	     && a.rd==b.rd
	   )
	       return true;
	   else
		   return false;

}



int main(){

	vector<instruction> ArrayListOFinstructionlist;
	struct instruction instructionList;

	char TEMPbuffer[SIZE];
	char temprs[7],temprt[7],temprd[7],tempfunction[3];
	int tempregister,tempindex,templabel;
	int TEMProw=0;

	//初始值宣告
	int Memory[32]={};   //w0~w31=1
	int Register[32]={}; //$0=0 , $1~$31=1
	for(int i=0;i<32;i++){
		Memory[i]=1;
		if(i!=0)
			Register[i]=1;
	}

	//寫檔宣告
	char filename[]=OUTPUT;
	fstream file2;

//讀檔開始
	fstream file;
	file.open(INPUT);
	if(!file)
	{
		cout<<"開檔失敗!\n";
		system("pause");
		return 0;
	}
	else
	{

		while(!file.eof()){

		

		if(file.getline(TEMPbuffer,sizeof(TEMPbuffer))==NULL)
			break;
		for(int i=0;TEMPbuffer[i]!='\0';i++)
		{
			if(TEMPbuffer[i]==',')
				TEMPbuffer[i]=' ';
		}


		TEMProw++;
		
		if(TEMPbuffer[0]=='l' && TEMPbuffer[1]=='w'){//lw
			
			sscanf (TEMPbuffer,"%s %s %s",tempfunction,temprt,temprs);
			
			//設定function參數
			instructionList.function=1;
			
			//設定rt的值
			temprt[0]=' '; //把$去掉
			sscanf(temprt,"%d",&tempregister);
			instructionList.rt=tempregister;

			//設定rs的值
			for(int i=0;temprs[i]!='\0';i++){
				if(temprs[i]=='(' || temprs[i]==')' || temprs[i]=='$')
					temprs[i]=' ';//把($ )去掉
			}			
			sscanf(temprs,"%d %d",&tempindex,&tempregister);
			instructionList.rs=tempregister;
			instructionList.immediateOrLabel=tempindex/4;

			cout<<"instruction : "<<instructionList.function<<" rs : "<<instructionList.rs<<" rt : "<<instructionList.rt<<" immediateOrLabel : "<<instructionList.immediateOrLabel<<endl;

		}
		else if(TEMPbuffer[0]=='s' && TEMPbuffer[1]=='w'){//sw

			sscanf (TEMPbuffer,"%s %s %s",tempfunction,temprt,temprs);
			//設定function參數
			instructionList.function=2;
			
			//設定rt的值
			temprt[0]=' '; //把$去掉
			sscanf(temprt,"%d",&tempregister);
			instructionList.rt=tempregister;

			//設定rs的值
			for(int i=0;temprs[i]!='\0';i++){
				if(temprs[i]=='(' || temprs[i]==')' || temprs[i]=='$')
					temprs[i]=' ';//把($ )去掉
			}			
			sscanf(temprs,"%d %d",&tempindex,&tempregister);
			instructionList.rs=tempregister;
			instructionList.immediateOrLabel=tempindex/4;

			cout<<"instruction : "<<instructionList.function<<" rs : "<<instructionList.rs<<" rt : "<<instructionList.rt<<" immediateOrLabel : "<<instructionList.immediateOrLabel<<endl;

		}
		else if(TEMPbuffer[0]=='b' && TEMPbuffer[1]=='e' && TEMPbuffer[2]=='q'){//beq
	
			sscanf (TEMPbuffer,"%s %s %s %d",tempfunction,temprt,temprs,&templabel);
			//設定function參數
			instructionList.function=3;

			temprs[0]=' ',temprt[0]=' ';//把$去掉
			sscanf (temprs,"%d",&tempregister);
			instructionList.rs=tempregister;
			sscanf (temprt,"%d",&tempregister);
			instructionList.rt=tempregister;

			instructionList.immediateOrLabel=templabel;

			cout<<"instruction : "<<instructionList.function<<" rs : "<<instructionList.rs<<" rt : "<<instructionList.rt<<" immediateOrLabel : "<<instructionList.immediateOrLabel<<endl;

		}
		else if(TEMPbuffer[0]=='a' && TEMPbuffer[1]=='d' && TEMPbuffer[2]=='d'){//add

			sscanf (TEMPbuffer,"%s %s %s %s",tempfunction,temprd,temprs,temprt);
			//設定function參數
			instructionList.function=4;

			temprs[0]=' ',temprt[0]=' ',temprd[0]=' ';//把$去掉
			sscanf (temprs,"%d",&tempregister);
			instructionList.rs=tempregister;
			sscanf (temprt,"%d",&tempregister);
			instructionList.rt=tempregister;
			sscanf (temprd,"%d",&tempregister);
			instructionList.rd=tempregister;

			cout<<"instruction : "<<instructionList.function<<" rs : "<<instructionList.rs<<" rt : "<<instructionList.rt<<" rd : "<<instructionList.rd<<endl;

		}
		else if(TEMPbuffer[0]=='s' && TEMPbuffer[1]=='u' && TEMPbuffer[2]=='b'){//sub

			sscanf (TEMPbuffer,"%s %s %s %s",tempfunction,temprd,temprs,temprt);
			//設定function參數
			instructionList.function=5;

			temprs[0]=' ',temprt[0]=' ',temprd[0]=' ';//把$去掉
			sscanf (temprs,"%d",&tempregister);
			instructionList.rs=tempregister;
			sscanf (temprt,"%d",&tempregister);
			instructionList.rt=tempregister;
			sscanf (temprd,"%d",&tempregister);
			instructionList.rd=tempregister;

			cout<<"instruction : "<<instructionList.function<<" rs : "<<instructionList.rs<<" rt : "<<instructionList.rt<<" rd : "<<instructionList.rd<<endl;

		}


		ArrayListOFinstructionlist.push_back(instructionList);//把instructionList丟進ArrayListOFinstructionlist的最後一個位置


     	}
		file.close();
	}//讀檔結束

		//cout<<TEMProw<<"行"<<endl;
	    
	struct instruction zeroInstruction;
	zeroInstruction.rd=0;
	zeroInstruction.rt=0;
	zeroInstruction.rs=0;
	zeroInstruction.immediateOrLabel=0;
	zeroInstruction.function=0;

	//指令初始化
	instruction iFInstruction = zeroInstruction;
	instruction iDinInstruction = zeroInstruction;
	instruction eXinInstruction = zeroInstruction;
	instruction mEMiInstruction = zeroInstruction;
	instruction wBiInstruction = zeroInstruction;
	
	//forwarding用參數
	int EXALUout = 0, MEMALUout = 0, WBALUout = 0;
	//記錄參數(除錯用，無參與運算)
	int writeData = 0, readData = 0;

		/*
		 * Start 
		 */
		int i = 0;
		int cycle = 0;
		bool stallFlag = false;
		while (true){
			/*
			 * to next CC
			 */
			if (stallFlag){
				wBiInstruction = mEMiInstruction;
				mEMiInstruction = eXinInstruction;
				eXinInstruction = zeroInstruction;

				i--;
				stallFlag = false;
			} else{
				wBiInstruction = mEMiInstruction;
				mEMiInstruction = eXinInstruction;
				eXinInstruction = iDinInstruction;
				iDinInstruction = iFInstruction;

				try {
					iFInstruction = ArrayListOFinstructionlist.at(i);
					//若beq還在ID階段，則不抓新指令
					if(iDinInstruction.function==3)
						iFInstruction = zeroInstruction;
				} catch (exception e) {
					// TODO: handle exception
					iFInstruction = zeroInstruction;
				}
			}

			
			// AlUout next
			WBALUout = MEMALUout;
			MEMALUout = EXALUout;
		

			
			
			//LoopStop check
			if (Struct1EStruct2(iFInstruction,zeroInstruction)
					&& Struct1EStruct2(wBiInstruction,zeroInstruction)
					&& Struct1EStruct2(iDinInstruction,zeroInstruction)
					&& Struct1EStruct2(eXinInstruction,zeroInstruction)
					&& Struct1EStruct2(mEMiInstruction,zeroInstruction))
				break;

			//Lwhazard detect
			if (eXinInstruction.function==1){//MemRead : lw
				if((eXinInstruction.rt == iDinInstruction.rs)
						|| eXinInstruction.rt == iDinInstruction.rt){
					stallFlag = true;
					cout<<"Instruction stall"<<endl;
				}

			}//Lwhazard detect (beq特別處理)
			if (mEMiInstruction.function==1 && iDinInstruction.function==3){//MemRead : lw  說明:beq較特別，若有hazard，要等lw的wb結束才能開始exe階段
				if((mEMiInstruction.rt == iDinInstruction.rs)
						|| mEMiInstruction.rt == iDinInstruction.rt){
					stallFlag = true;
					cout<<"Instruction stall"<<endl;
				}

			}
			//beq特別處理ver.2
			if ( (eXinInstruction.function==4 || eXinInstruction.function==5) && iDinInstruction.function==3){//說明:beq較特別，若有hazard，要等add sub的Mem結束才能開始exe階段
				if((eXinInstruction.rd == iDinInstruction.rs)
						|| eXinInstruction.rd == iDinInstruction.rt){
					stallFlag = true;
					cout<<"Instruction stall"<<endl;
				}

			}

			//wb
			switch (wBiInstruction.function) {
			case 1://lw
				//Register[wBiInstruction.rt] = Memory[Register[wBiInstruction.rs]+wBiInstruction.immediateOrLabel];
				Register[wBiInstruction.rt] = WBALUout;
				break;
			case 2://sw
				break;
			
			case 4://add
			case 5://sub	
				Register[wBiInstruction.rd] = WBALUout;
				break;

			default:
				break;
			}
			
			//mem
			switch (mEMiInstruction.function) {
			case 1://lw
				readData = Register[mEMiInstruction.rt];
				break;
			case 2://sw
				Memory[Register[mEMiInstruction.rs]+mEMiInstruction.immediateOrLabel] = Register[mEMiInstruction.rt];
				readData = 0;
				break;
			
			case 4://add
			case 5://sub	
				readData = 0;
				break;

			default:
				readData = 0;
				break;
			}


			//execution
			//dataHazard detect
			int hazardrs = Register[eXinInstruction.rs];
			int hazardrt = Register[eXinInstruction.rt];
			     //EX hazard
			if ( (mEMiInstruction.function==4 || mEMiInstruction.function==5) && mEMiInstruction.rd!=0 ){ //mEM.RegWrite :add sub (lw不用管->lw hazard) 
				if (mEMiInstruction.rd == eXinInstruction.rs){
					hazardrs = MEMALUout; //forwarding
					cout<<"datahazard(ex) detected"<<endl;
					cout<<"hazardrs = "<<hazardrs<<endl;
					
					
				}
				else if(mEMiInstruction.rd == eXinInstruction.rt){
					hazardrt = MEMALUout; //forwarding
					cout<<"datahazard(ex) detected"<<endl;
					cout<<"hazardrt = "<<hazardrt<<endl;
				
					
				}
			}
			     //Mem hazard
			else if( (wBiInstruction.function==4 || wBiInstruction.function==5) && wBiInstruction.rd!=0 ){ //WB.RegWrite :add sub (lw不用管->lw hazard) 
				if (wBiInstruction.rd == eXinInstruction.rs){
					hazardrs = MEMALUout; //forwarding
					cout<<"datahazard(Mem) detected"<<endl;
					cout<<"hazardrs = "<<hazardrs<<endl;
				
					
				}
				else if(wBiInstruction.rd == eXinInstruction.rt){
					hazardrt = MEMALUout; //forwarding
					cout<<"datahazard(Mem) detected"<<endl;
					cout<<"hazardrt = "<<hazardrt<<endl;
					
					
				}
			}

			//main execution
			switch (eXinInstruction.function) {
			case 1://lw
				EXALUout = Memory[Register[eXinInstruction.rs]+eXinInstruction.immediateOrLabel];
				writeData = 0;
				break;
			case 2://sw
				EXALUout = Register[eXinInstruction.rt];
				writeData = Register[eXinInstruction.rt];
				break;
			case 3://beq
				if (hazardrs == hazardrt){//若相等則抓相對應位置的指令
					cout<<"beq rs : "<<hazardrs<<" rt : "<<hazardrt<<endl;
					i = i + eXinInstruction.immediateOrLabel -1;
					iDinInstruction = zeroInstruction; //清掉在beq執行時抓的下一行指令
					try {
						iFInstruction = ArrayListOFinstructionlist.at(i);
					} catch (exception e) {
						iFInstruction = zeroInstruction;
					}
				}
				else{//若不相等則抓下一行指令
					cout<<"neq rs : "<<hazardrs<<" rt : "<<hazardrt<<endl;
					i=i-1;
					try {
						iFInstruction = ArrayListOFinstructionlist.at(i);
					} catch (exception e) {
						iFInstruction = zeroInstruction;
					}
				}

				EXALUout = 0;
				writeData = 0;
				break;
			case 4://add
				EXALUout = hazardrs + hazardrt;
				Register[eXinInstruction.rd] = hazardrs + hazardrt;
				cout<<"$"<<eXinInstruction.rd<<" : "<<Register[eXinInstruction.rd]<<" rs : "<<hazardrs<<" + rt : "<<hazardrt<<endl;
				writeData = 0;
				break;
			case 5://sub	
				EXALUout = hazardrs - hazardrt;
				Register[eXinInstruction.rd] = hazardrs - hazardrt;
				cout<<"$"<<eXinInstruction.rd<<" : "<<Register[eXinInstruction.rd]<<" rs : "<<hazardrs<<" - rt : "<<hazardrt<<endl;
				writeData = 0;
				break;	

			default:
				//EXALUout = 0;
				writeData = 0;
				break;
			}
			
			//ID
			switch (iDinInstruction.function) {
			case 1://lw
			case 2://sw
				break;
			case 3://beq
				break;
			}


			/*
			 * print Segement
			 */
			cout<<"Cycle "<<cycle+1<<"\n";
			//cout<<"WBALUout : "<<WBALUout<<" MEMALUout : "<<MEMALUout<<" EXALUout : "<<EXALUout<<endl;
			if(!Struct1EStruct2(wBiInstruction,zeroInstruction)){

				switch(wBiInstruction.function){
			    case 1:
					cout<<"lw : WB\n";
					break;
				case 2:
					cout<<"sw : WB\n";
					break;
				case 3:
					cout<<"bep : WB\n";
					break;
				case 4:
					cout<<"add : WB\n";
					break;
				case 5:
					cout<<"sub : WB\n";
					break;
			     }
			}

			if(!Struct1EStruct2(mEMiInstruction,zeroInstruction)){

				switch(mEMiInstruction.function){
			    case 1:
					cout<<"lw : MEM\n";
					break;
				case 2:
					cout<<"sw : MEM\n";
					break;
				case 3:
					cout<<"bep : MEM\n";
					break;
				case 4:
					cout<<"add : MEM\n";
					break;
				case 5:
					cout<<"sub : MEM\n";
					break;
			     }
			}		
					
			if(!Struct1EStruct2(eXinInstruction,zeroInstruction)){

				switch(eXinInstruction.function){
			    case 1:
					cout<<"lw : EX\n";
					break;
				case 2:
					cout<<"sw : EX\n";
					break;
				case 3:
					cout<<"bep : EX\n";
					break;
				case 4:
					cout<<"add : EX\n";
					break;
				case 5:
					cout<<"sub : EX\n";
					break;
			     }
			}
					

			if(!Struct1EStruct2(iDinInstruction,zeroInstruction)){

				switch(iDinInstruction.function){
			    case 1:
					cout<<"lw : ID\n";
					break;
				case 2:
					cout<<"sw : ID\n";
					break;
				case 3:
					cout<<"bep : ID\n";
					break;
				case 4:
					cout<<"add : ID\n";
					break;
				case 5:
					cout<<"sub : ID\n";
					break;
			     }
			}

			if(!Struct1EStruct2(iFInstruction,zeroInstruction)){

				switch(iFInstruction.function){
			    case 1:
					cout<<"lw : IF\n";
					break;
				case 2:
					cout<<"sw : IF\n";
					break;
				case 3:
					cout<<"bep : IF\n";
					break;
				case 4:
					cout<<"add : IF\n";
					break;
				case 5:
					cout<<"sub : IF\n";
					break;
			     }
			}
						
			cout<<"=================================================================\n";


			/*
			 * Fileprint Segement
			 */
////第一階段寫檔開始
				
				file2.open((char*) filename, ios::app);      //以append模式開啟檔案，準備寫入
        if(!file2)     //檢查檔案是否成功開啟

        {

                cerr << "Can't open file!\n";

                exit(1);     //在不正常情形下，中斷程式的執行

        }

		else
		{
			file2<<"Cycle "<<cycle+1<<"\n";
			if(!Struct1EStruct2(wBiInstruction,zeroInstruction)){

				switch(wBiInstruction.function){
			    case 1:
					file2<<"lw : WB\n";
					break;
				case 2:
					file2<<"sw : WB\n";
					break;
				case 3:
					file2<<"bep : WB\n";
					break;
				case 4:
					file2<<"add : WB\n";
					break;
				case 5:
					file2<<"sub : WB\n";
					break;
			     }
			}

			if(!Struct1EStruct2(mEMiInstruction,zeroInstruction)){

				switch(mEMiInstruction.function){
			    case 1:
					file2<<"lw : MEM\n";
					break;
				case 2:
					file2<<"sw : MEM\n";
					break;
				case 3:
					file2<<"bep : MEM\n";
					break;
				case 4:
					file2<<"add : MEM\n";
					break;
				case 5:
					file2<<"sub : MEM\n";
					break;
			     }
			}		
					
			if(!Struct1EStruct2(eXinInstruction,zeroInstruction)){

				switch(eXinInstruction.function){
			    case 1:
					file2<<"lw : EX\n";
					break;
				case 2:
					file2<<"sw : EX\n";
					break;
				case 3:
					file2<<"bep : EX\n";
					break;
				case 4:
					file2<<"add : EX\n";
					break;
				case 5:
					file2<<"sub : EX\n";
					break;
			     }
			}
					

			if(!Struct1EStruct2(iDinInstruction,zeroInstruction)){

				switch(iDinInstruction.function){
			    case 1:
					file2<<"lw : ID\n";
					break;
				case 2:
					file2<<"sw : ID\n";
					break;
				case 3:
					file2<<"bep : ID\n";
					break;
				case 4:
					file2<<"add : ID\n";
					break;
				case 5:
					file2<<"sub : ID\n";
					break;
			     }
			}

			if(!Struct1EStruct2(iFInstruction,zeroInstruction)){

				switch(iFInstruction.function){
			    case 1:
					file2<<"lw : IF\n";
					break;
				case 2:
					file2<<"sw : IF\n";
					break;
				case 3:
					file2<<"bep : IF\n";
					break;
				case 4:
					file2<<"add : IF\n";
					break;
				case 5:
					file2<<"sub : IF\n";
					break;
			     }
			}
			file2<<"\n";
		}
		file2.close();
//第一階段寫檔結束



			i++;
			cycle++;

		}//end while


		    /*
			 * print Segement
			 */
			cout<<"Registers:\n";
			for(int j = 0; j < 32; j++){
				cout<<"$"<<j<<"\t: "<<Register[j]<<"\t";
			}
			cout<<"\n";
			cout<<"Data memory:\n";
			for(int j = 0; j < 32; j++){
				cout<<"W"<<j<<"\t: "<<Memory[j]<<"\t";
			}
			cout<<"\n";

			/*
			 * Fileprint Segement
			 */
//第二階段寫檔開始
			file2.open((char*) filename, ios::app);      //以append模式開啟檔案，準備寫入
        if(!file2)     //檢查檔案是否成功開啟
        {

                cerr << "Can't open file!\n";

                exit(1);     //在不正常情形下，中斷程式的執行

        }
		else{
			file2<<"Registers:\n";
			for(int j = 0; j < 32; j++){
				file2<<"$"<<j<<"\t: "<<Register[j]<<"\t";
				if((j+1)%5==0)
					file2<<"\n";
			}
			file2<<"\n\n";
			file2<<"Data memory:\n";
			for(int j = 0; j < 32; j++){
				file2<<"W"<<j<<"\t: "<<Memory[j]<<"\t";
				if((j+1)%5==0)
					file2<<"\n";
			}
			file2<<"\n";
		}

	file2.close();
//第二階段寫檔結束

		system("pause");

		return 0;
}