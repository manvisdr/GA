#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>

using namespace std;
int nx,ny,x,y;
float total_fitness = 0;

int main()
{
    //---initial---
    srand(time(NULL));
    float fobj[x];
    float fitness[x],prob[x];
	float cum=0;
	float cump[x];
	cump[x]=0;
	float pc = 0.5;
	cout << "jml chromosome: "; cin >> nx;
    cout << "jml gen: "; cin >> ny;
    //cout << "input pc: "; cin >> pc;
    int matrix[nx][ny];
	for (x = 1; x <= nx; x++)
        for (y = 1; y <= ny; y++)
			matrix[x][y] = (rand()%10+1);
	for (x = 1; x <= nx; x++)
	{
	    cout << "Chromosome"<<"["<<x<<"] : ";
	   	for (y = 1; y <= ny; y++)
        cout << matrix[x][y] << "   ";
        cout << endl;
	}
	cout << "-------------------------------------" << endl;

	for (x = 1; x <= nx; x++)
    {
        //fobj
        fobj[x]=fabs(matrix[x][1]+(2*matrix[x][2])+(3*matrix[x][3])+(4*matrix[x][4])-30);
        //---Fitness---
        fitness[x]=(1/(1+(fobj[x])));
        total_fitness=total_fitness+fitness[x];
        cout << "F.Objektif"<<"["<<x<<"] : ";
        cout << fobj[x] << "   ";
        cout << "Fitness"<<"["<<x<<"] : ";
        cout << fitness[x] << "    ";
        cout << endl;
    }
    cout << "Total Fitness : " ;
    cout << total_fitness << "    ";
    cout << endl;
    cout << "-------------------------------------" << endl;
    for (x = 1; x <= nx; x++)
    {
        //---Probabilitas---
        prob[x]=fitness[x]/total_fitness;
        cum += prob[x];
        cump[x]=cum;
        cout << "Probabilitas"<<"["<<x<<"] : ";
        cout << prob[x] << "    ";
        cout << "CUM.Prob"<<"["<<x<<"] : ";
        cout << cum << "    ";
        cout << endl;

    }
    cout <<"---------------------------------------" << endl;
    float rand1 [nx], R[nx];
    int next[nx];
    for (int i=1;i<=nx;i++)
    {
        rand1 [i]= (rand()%1000);
        R[i] = rand1 [i]/1000;
        cout << "Rand.Sel" <<" [" << i << "] " << ": ";
        cout << R[i] << " ";
        for (int j=0;j<=nx;j++)
        {
            if (R[i]>cump[j])
            {
                next[i]=j+1;
            }
        }
        cout << "ChromNew [" << i << "] = " << "Chromsome [" << next[i] << "]" <<endl;
    }
    // Mengkopi Chromosome
    cout << "Mengkopi chromosome yang terpilih" << endl;
    cout << "-------------------------------------" << endl;
    for(int i=1;i<=nx;i++)
    {
        cout << "ChromNew [" << i << "] = [";
        for (int j=1;j<=ny;j++)
        {
            cout << matrix[next[i]][j] <<";";
        }
        cout <<"]"<< endl;
    }
    cout << "-------------------------------------" << endl;

// memilih induk yang akan di crossover
    int i, induk[nx];
    float ranpc [nx], Rpc[nx];
    float cpc[nx];
    float randi [nx], R3[nx];
    int jc=0, jp=0;
    float value = 0.0f;
    int num [nx];
    for (i=1;i<=nx;i++){
        ranpc [i]= rand()%1000;
        Rpc[i] = ranpc [i]/1000;
        num[i]=i;
        //num=1;
        cout << "Rand.C" <<" [" << i << "] " << "= " << Rpc[i]<< " " ;
        cout << " -> Num.C" <<" [" << i << "] " << "= " << num[i]<< " " << endl;
    }

	//Proses sorting
	int j;
    int indek = 0;
    for(i=1;i<=nx-1;i++){
    	for(j=i+1;j<=nx;j++){
        	if(Rpc[i]>Rpc[j]){		//proses swap menukar posisi
           		value = Rpc[j];
           		indek = num[j];
           		Rpc[j] = Rpc[i];
           		num[j] = num[i];
           		Rpc[i] = value;
           		num [i] = indek;
        	}
        }
        cout << "Rand.C-Sort" <<" [" << num [i] << "] " << "= ";
        cout << Rpc[i]<< " ";

        if(Rpc[i]<pc){					// jika random kurang dari probabilitas crossover
           	//cpc[i]=i;
           	jc++;
        }
        //else
        //cpc[i]=0;

        //induk[i]=cpc[i];
		cout<<"\t Induk ["<<i<<"] = "<<num[i]<<endl;
    }
    cout << "Rand.C-Sort" <<" [" << num [nx] << "] " << "= ";		//mencatat individu terakhir
    cout << Rpc[nx]<< " ";
    cout<<"\t Induk ["<<i<<"] = "<<num[nx]<<endl;

	jp=round(jc/2);


    cout << "-------------------------------------" << endl;
    cout << "Jumlah induk = "<<jc<<endl;
    cout << "Jumlah pasangan = "<<jp<<endl;


	// Proses Crossover
	// Menentukan induk
	int Pc, buf, indukganjil, indukgenap, no_in1, no_in2, induk1[ny], induk2[ny], indukbaru[nx];

	for(int i=1; i<=jp; i++)
    {
    	indukganjil=2*i-1;
    	indukgenap=2*i;
    	no_in1=num[indukganjil];
    	no_in2=num[indukgenap];
    	cout << "\n in1 = " << indukganjil << "\t induk 1 = " << no_in1;			//ceking induk yang dipilih
		cout << "\n in2 = " << indukgenap << "\t induk 2 = " << no_in2 <<endl;

		//cout << " \n Induk1 =  " ;
		cout << " \n Induk <"<<i<<"> =  " <<"[";
		for (int j=1;j<=ny;j++){
			induk1[j]=matrix[no_in1][j];
			cout << induk1[j] << ";";
		}
		cout <<"]" <<endl;
		//cout << " \n Induk2 =  " ;
		cout << " Induk <"<<i<<"> =  " <<"[";
		for (int j=1;j<=ny;j++){
			induk2[j]=matrix[no_in2][j];
			cout << induk2[j] << ";";
		}
		cout <<"]" <<endl;

		//penentuan titik crossover
		Pc =rand()%(ny-1)+1;
		cout << "Pc = " << Pc << endl;

		cout <<"--------------------------\n";
		cout <<"hasil crossover = \n";
		cout <<"Induk1 \t Induk2 \n";
		//cout << "Chrom.Crossover [" << i << "] = [";

		for (int j=1;j<=ny;j++){

			if (j<=Pc){
				buf	= induk1[j];
				induk1[j]=induk2[j];
				induk2[j]=buf;

				cout << induk1[j] << "\t";
				cout << induk2[j] << "\n";
				cout << induk1[j] << " ";
				cout << induk2[j] << " ";
			}
			else{
				induk1[j]=induk1[j];
				induk2[j]=induk2[j];
				cout << induk1[j] << "\t";
				cout << induk2[j] << "\n";
			}
			//cout << matrix[next[i]][induk1[j]] <<"  ";
			//cout <<"]"<< endl;
		}
    }
    float pm=0.1;
    int total_gen=0,jml_mutasi,randmut;
    total_gen=nx*ny;
    jml_mutasi=pm*total_gen;
    cout<<"Total Gen = "<<total_gen<<" --> ";
    cout<<" Jumlah.Mutasi = "<<jml_mutasi<<endl;
    for(int i=1; i<=jml_mutasi; i++)
    {
        randmut=rand()%total_gen+1;
        cout<<"Posisi Gen [" << i << "] = "<<randmut<<endl;
    }

}
