// Konzolna aplikacija za vcituvanje na dva broja od tekstualni datoteki
// i aritmeticki operacii so niv

//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

#define BR_CIFRI 20

using namespace std;

void sobiranje(short brojA[], short brojB[], int dolzinaA, int dolzinaB, short broj[])
{
	short zbir[BR_CIFRI];
	for (int i = 0; i < BR_CIFRI; i++)
		zbir[i] = 0;
	for (int i = BR_CIFRI - 1; i >= BR_CIFRI - dolzinaA - 1 || i >= BR_CIFRI - dolzinaB - 1; i--)
	{
		zbir[i] = zbir[i] + brojA[i] + brojB[i];
		if (zbir[i] >= 10)
        {
			zbir[i] = zbir[i] - 10;
            if (i - 1 >= 0)
				zbir[i - 1] = 1;
        }
	}
	for (int i = 0; i < BR_CIFRI; i++)
		broj[i] = zbir[i];
	return;
}

void odzemanje(short brojA[], short brojB[], short broj[], bool &negativen)
{
	short razlika[BR_CIFRI];
	for (int i = 0; i < BR_CIFRI; i++)
		razlika[i] = 0;
	bool prvPogolem = true;
	bool sigurno = false;
	for (int i = 0; sigurno == false && i < BR_CIFRI; i++)
		if (brojA[i] > brojB[i])
			sigurno = true;
		else if (brojA[i] < brojB[i])
		{
			sigurno = true;
			prvPogolem = false;
		}
	for (int i = 0; i < BR_CIFRI; i++)
		razlika[i] = 0;
	for (int i = BR_CIFRI - 1; i >= 0; i--)
	{
		if (prvPogolem)
		{
			razlika[i] = razlika[i] + (brojA[i] - brojB[i]);
			negativen = false;
		}
		else
		{
			razlika[i] = razlika[i] + (brojB[i] - brojA[i]);
			negativen = true;
		}
		if (razlika[i] < 0)
		{
			razlika[i] = razlika[i] + 10;
			if (i - 1 >= 0)
				razlika[i - 1] = -1;
		}
	}
	for (int i = 0; i < BR_CIFRI; i++)
		broj[i] = razlika[i];
	return;
}

void mnozenje(short brojA[], short brojB[], short broj[], bool &uspesno)
{
	int dolzinaA = 0;
	int dolzinaB = 0;
	short proizvod[BR_CIFRI];
	for (int i = 0; i < BR_CIFRI; i++)
		proizvod[i] = 0;
	for (int i = 0; dolzinaA == 0 && i < BR_CIFRI; i++)
		if (brojA[i] != 0)
			dolzinaA = BR_CIFRI - i;
	for (int i = 0; dolzinaB == 0 && i < BR_CIFRI; i++)
		if (brojB[i] != 0)
			dolzinaB = BR_CIFRI - i;
	if (dolzinaA + dolzinaB <= BR_CIFRI)
	{
		for (int i = BR_CIFRI - dolzinaA; i < BR_CIFRI; i++)
			for (int j = BR_CIFRI - dolzinaB; j < BR_CIFRI; j++)
				if (BR_CIFRI - ((BR_CIFRI - i - 1) + (BR_CIFRI - j - 1)) - 1 >= 0 && BR_CIFRI - ((BR_CIFRI - i - 1) + (BR_CIFRI - j - 1)) - 1 < BR_CIFRI)
				{
					proizvod[BR_CIFRI - ((BR_CIFRI - i - 1) + (BR_CIFRI - j - 1)) - 1] = proizvod[BR_CIFRI - ((BR_CIFRI - i - 1) + (BR_CIFRI - j - 1)) - 1] + (brojA[i] * brojB[j]);
					if (proizvod[BR_CIFRI - ((BR_CIFRI - i - 1) + (BR_CIFRI - j - 1)) - 1] >= 10)
					{
						if (BR_CIFRI - ((BR_CIFRI - i - 1) + (BR_CIFRI - j - 1)) - 1 - 1 >= 0)
						{
							proizvod[BR_CIFRI - ((BR_CIFRI - i - 1) + (BR_CIFRI - j - 1)) - 1 - 1] = proizvod[BR_CIFRI - ((BR_CIFRI - i - 1) + (BR_CIFRI - j - 1)) - 1 - 1] + (proizvod[BR_CIFRI - ((BR_CIFRI - i - 1) + (BR_CIFRI - j - 1)) - 1] / 10);
							if (proizvod[BR_CIFRI - ((BR_CIFRI - i - 1) + (BR_CIFRI - j - 1)) - 1 - 1] >= 10)
							{
								if (BR_CIFRI - ((BR_CIFRI - i - 1) + (BR_CIFRI - j - 1)) - 1 - 2 >= 0)
									proizvod[BR_CIFRI - ((BR_CIFRI - i - 1) + (BR_CIFRI - j - 1)) - 1 - 2] = proizvod[BR_CIFRI - ((BR_CIFRI - i - 1) + (BR_CIFRI - j - 1)) - 1 - 2] + (proizvod[BR_CIFRI - ((BR_CIFRI - i - 1) + (BR_CIFRI - j - 1)) - 1 - 1] / 10);
								proizvod[BR_CIFRI - ((BR_CIFRI - i - 1) + (BR_CIFRI - j - 1)) - 1 - 1] = proizvod[BR_CIFRI - ((BR_CIFRI - i - 1) + (BR_CIFRI - j - 1)) - 1 - 1] % 10;
							}
						}
						proizvod[BR_CIFRI - ((BR_CIFRI - i - 1) + (BR_CIFRI - j - 1)) - 1] = proizvod[BR_CIFRI - ((BR_CIFRI - i - 1) + (BR_CIFRI - j - 1)) - 1] % 10;
					}
				}
	}
	else
		uspesno = false;
	for (int i = 0; i < BR_CIFRI; i++)
		broj[i] = proizvod[i];
}

void delenoSoDva(short brojA[], short broj[])
{
	int dolzinaA = 0;
	short delen[BR_CIFRI];
	for (int i = 0; dolzinaA == 0 && i < BR_CIFRI; i++)
		if (brojA[i] != 0)
			dolzinaA = BR_CIFRI - i;
	for (int i = 0; i < BR_CIFRI; i++)
		delen[i] = 0;
	for (int i = BR_CIFRI - dolzinaA - 1; i < BR_CIFRI - 1; i++)
		if (brojA[i] % 2 == 0)
			delen[i + 1] = brojA[i + 1] / 2;
		else
			delen[i + 1] = 5 + brojA[i + 1] / 2;
	for (int i = 0; i < BR_CIFRI; i++)
		broj[i] = delen[i];
	return;
}

void stepenuvanje(short brojA[], short brojB[], short broj[], bool &uspesno)
{
	if (uspesno)
	{
		int dolzinaA = 0;
		int dolzinaB = 0;
		short nMinusEden[BR_CIFRI];
		short nMinusEdenVrzDva[BR_CIFRI];
		short nVrzDva[BR_CIFRI];
		short eden[BR_CIFRI];
		bool negativen = false;
		short stepenuvan[BR_CIFRI];
		for (int i = 0; i < BR_CIFRI; i++)
		{
			stepenuvan[i] = 0;
			nMinusEden[i] = 0;
			nMinusEdenVrzDva[i] = 0;
			nVrzDva[i] = 0;
			eden[i] = 0;
		}
		eden[BR_CIFRI - 1] = 1;
		for (int i = 0; dolzinaA == 0 && i < BR_CIFRI; i++)
			if (brojA[i] != 0)
				dolzinaA = BR_CIFRI - i;
		for (int i = 0; dolzinaB == 0 && i < BR_CIFRI; i++)
			if (brojB[i] != 0)
				dolzinaB = BR_CIFRI - i;
		if (dolzinaB <= 1 && (brojB[BR_CIFRI - 1] == 2 || brojB[BR_CIFRI - 1] == 0))
		{
			if (brojB[BR_CIFRI - 1] == 2)
				mnozenje(brojA, brojA, stepenuvan, uspesno);
			else
				for (int i = 0; i < BR_CIFRI; i++)
					stepenuvan[i] = eden[i];
		}
		else
		{
			if (brojB[BR_CIFRI - 1] % 2 != 0) //ako e neparen
			{
				mnozenje(brojA, brojA, stepenuvan, uspesno); //x*x
				odzemanje(brojB, eden, nMinusEden, negativen);
				delenoSoDva(nMinusEden, nMinusEdenVrzDva);
				stepenuvanje(stepenuvan, nMinusEdenVrzDva, stepenuvan, uspesno);
				mnozenje(brojA, stepenuvan, stepenuvan, uspesno);
			}
			else
			{
				mnozenje(brojA, brojA, stepenuvan, uspesno); //x*x
				delenoSoDva(brojB, nVrzDva);
				stepenuvanje(stepenuvan, nVrzDva, stepenuvan, uspesno);
			}
		}
		for (int i = 0; i < BR_CIFRI; i++)
			broj[i] = stepenuvan[i];
	}
	else
		uspesno = false;
	return;
}

int sporedi(short int A[], short int B[])
{
    int dolzinaA=BR_CIFRI;
    int dolzinaB=BR_CIFRI;
    for(int i=0; i<BR_CIFRI;i++)
    {
        if(A[i]!=0)
            dolzinaA--;
        if(A[i+1]!=0 && i+1<BR_CIFRI)
            break;
    }
    for(int i=0; i<BR_CIFRI;i++)
    {
        if(B[i]!=0)
            dolzinaB--;
        if(B[i+1]!=0 && i+1<BR_CIFRI)
            break;
    }
    if(dolzinaA>dolzinaB)
        return 1;
    if(dolzinaA<dolzinaB)
        return -1;
    int brojac=0;
    for(int i=0;i<BR_CIFRI;i++)
    {
        if(A[i]==B[i])
            brojac++;
        if(A[i+1]!=B[i+1] && i+1<BR_CIFRI)
            break;
    }
    if(brojac==BR_CIFRI)
        return 0;
    bool prv_pogolem=false;
    for(int i=0;i<BR_CIFRI;i++)
    {
        if(A[i]>=B[i])
        {
            if(A[i]>B[i])
                return 1;
            if(A[i+1]<B[i+1] && i+1<BR_CIFRI)
                return -1;
        }
        else
            return -1;
    }
}

bool dali_e_prost(short int n[], int dolzina)
{
    int dolzina_i=0;
    if(dolzina==1)
    {
        if(n[BR_CIFRI-1]==0 || n[BR_CIFRI-1]==1) //ako e 0 ili 1
            return false;
        if(n[BR_CIFRI-1]==2 || n[BR_CIFRI-1]==3) // ako e 2 ili 3
            return true;
    }
    if(n[BR_CIFRI-1]%2==0) // ako n%2==0
        return false;
    int zbir_cifri=0;
    for(int i=0;i<BR_CIFRI;i++)
        zbir_cifri=(zbir_cifri+n[i])%3;
    if(zbir_cifri%3==0) // ako n%3==0
        return false;
    if(n[BR_CIFRI-1]%5==0) // ako n%5==0
        return false;
    short int brojac[BR_CIFRI];
    for(int i=0;i<BR_CIFRI;i++)
        brojac[i]=0;
    brojac[BR_CIFRI-1]=5;
    bool uspesno=true;
    while(true)
    {
        dolzina_i=0;
        short int rezultat[BR_CIFRI];
        for(int i=0;i<BR_CIFRI;i++)
            rezultat[i]=0;
        mnozenje(brojac,brojac,rezultat,uspesno);
        if(sporedi(rezultat,n)==-1 || sporedi(rezultat,n)==0) // if i*i<=n
        {
            if(sporedi(rezultat,n)==-1) // if i*i<n
            {
                short int ostatok[BR_CIFRI];
                for(int i=0;i<BR_CIFRI;i++)
                    ostatok[i]=0;
                short int delenik[BR_CIFRI];
                for(int i=0; i<BR_CIFRI;i++)
                    delenik[i]=n[i];
                while(sporedi(delenik,brojac)==1)
                {
                    bool p=false;
                    odzemanje(delenik,brojac,ostatok,p);
                    for(int i=0;i<BR_CIFRI;i++)
                        delenik[i]=ostatok[i];
                }
                short int pomosna1[BR_CIFRI];
                for(int i=0;i<BR_CIFRI;i++)
                    pomosna1[i]=0;
                if(sporedi(delenik,pomosna1)==0)
                    return false;
                if(sporedi(delenik,brojac)==0)
                    return false;
            }
            else // i*i=n
            {
                return false;
            }
        }
        else // i*i>n
        {
            return true;
        }
        short int dva[BR_CIFRI];
        for(int i=0;i<BR_CIFRI;i++)
            dva[i]=0;
        dva[BR_CIFRI-1]=2;
        short int pomosna[BR_CIFRI];
        for(int i=0;i<BR_CIFRI;i++)
            pomosna[i]=0;
        for(int i=0;i<BR_CIFRI;i++)
            if(brojac[i]==0)
            {
                dolzina_i++;
                if(brojac[i+1]!=0  && i+1<BR_CIFRI)
                    break;
            }
        sobiranje(brojac,dva,BR_CIFRI-dolzina_i,1,pomosna); // i=i+2
        for(int i=0;i<BR_CIFRI;i++)
            brojac[i]=pomosna[i];
        for(int i=0;i<BR_CIFRI;i++)
            rezultat[i]=0;
        mnozenje(brojac,brojac,rezultat,uspesno);
        if(sporedi(rezultat,n)==-1 || sporedi(rezultat,n)==0) // if i*i<=n
        {
            if(sporedi(rezultat,n)==-1) // if i*i<n
            {
                short int ostatok[BR_CIFRI];
                for(int i=0;i<BR_CIFRI;i++)
                    ostatok[i]=0;
                short int delenik[BR_CIFRI];
                for(int i=0; i<BR_CIFRI;i++)
                    delenik[i]=n[i];
                while(sporedi(delenik,brojac)==1)
                {
                    bool p=false;
                    odzemanje(delenik,brojac,ostatok,p);
                    for(int i=0;i<BR_CIFRI;i++)
                        delenik[i]=ostatok[i];
                }
                short int pomosna1[BR_CIFRI];
                for(int i=0;i<BR_CIFRI;i++)
                    pomosna1[i]=0;
                if(sporedi(delenik,pomosna1)==0)
                    return false;
            }
            else // i*i=n
            {
                return false;
            }
        }
        else // i*i>n
        {
            return true;
        }
        short int cetiri[BR_CIFRI];
        for(int i=0;i<BR_CIFRI;i++)
            cetiri[i]=0;
        cetiri[BR_CIFRI-1]=4;
        for(int i=0;i<BR_CIFRI;i++)
            pomosna[i]=0;
        dolzina_i=0;
        for(int i=0;i<BR_CIFRI;i++)
            if(brojac[i]==0)
            {
                dolzina_i++;
                if(brojac[i+1]!=0 && i+1<BR_CIFRI)
                    break;
            }
        sobiranje(brojac,cetiri,BR_CIFRI-dolzina_i,1,pomosna); // i=i+4
    }
}


int main()
{
	short broj[BR_CIFRI];
	int dolzina = 0;
	bool negativen = false;
	bool uspesno = true;
	short brojA[BR_CIFRI];
	int dolzinaA = 0;
	short brojB[BR_CIFRI];
	int dolzinaB = 0;
	ifstream infile;

	for (int i = 0; i < BR_CIFRI; i++)
	{
		broj[i] = 0;
		brojA[i] = 0;
		brojB[i] = 0;
	}

	infile.open("broja.txt", ifstream::in);
	while (infile.good())
	{
		broj[dolzina] = infile.get() - '0';
		dolzina++;
	}
	infile.close();
	dolzina--;

	for (int i = 0; i < dolzina; i++)
		brojA[(BR_CIFRI - dolzina) + i] = broj[i];
	dolzinaA = dolzina;

	dolzina = 0;
	infile.open("brojb.txt", ifstream::in);
	while (infile.good())
	{
		broj[dolzina] = infile.get() - '0';
		dolzina++;
	}
	infile.close();
	dolzina--;

	for (int i = 0; i < dolzina; i++)
		brojB[(BR_CIFRI - dolzina) + i] = broj[i];
	dolzinaB = dolzina;


	dolzina = 0;
	if (dolzinaA >= 1 && dolzinaB >= 1)
	{
		cout << "Prviot broj ima " << dolzinaA << " cifri, negovata vrednost e: " << endl;
		for (int i = BR_CIFRI - dolzinaA; i < BR_CIFRI; i++)
			cout << brojA[i];
		cout << endl << endl;

		cout << "Vtoriot broj ima " << dolzinaB << " cifri, negovata vrednost e: " << endl;
		for (int i = BR_CIFRI - dolzinaB; i < BR_CIFRI; i++)
			cout << brojB[i];
		cout << endl << endl;

		///// naogjanje zbir:
		sobiranje(brojA, brojB, dolzinaA, dolzinaB, broj);

		for (int i = 0; dolzina == 0 && i < BR_CIFRI; i++)
			if (broj[i] != 0)
				dolzina = BR_CIFRI - i;

		cout << "Zbirot na dvata broja e: " << endl;
		for (int i = BR_CIFRI - dolzina; i < BR_CIFRI; i++)
			cout << broj[i];
		cout << endl << endl;


		///// naogjanje razlika:
		odzemanje(brojA, brojB, broj, negativen);
		dolzina = 0;
		for (int i = 0; dolzina == 0 && i < BR_CIFRI; i++)
			if (broj[i] != 0)
				dolzina = BR_CIFRI - i;

		cout << "Razlikata na dvata broja e: " << endl;
		if (negativen)
			cout << "-";
		for (int i = BR_CIFRI - dolzina; i < BR_CIFRI; i++)
			cout << broj[i];
		cout << endl << endl;

		///// naogjanje proizvod:
		mnozenje(brojA, brojB, broj, uspesno);
		if (uspesno)
		{
			dolzina = 0;
			for (int i = 0; dolzina == 0 && i < BR_CIFRI; i++)
				if (broj[i] != 0)
					dolzina = BR_CIFRI - i;
			cout << "Proizvodot na dvata broja e: " << endl;
			for (int i = BR_CIFRI - dolzina; i < BR_CIFRI; i++)
				cout << broj[i];
			cout << endl << endl;
		}

		///// naogjanje stepen:
		stepenuvanje(brojA, brojB, broj, uspesno);
		if (uspesno)
		{
			dolzina = 0;
			for (int i = 0; dolzina == 0 && i < BR_CIFRI; i++)
				if (broj[i] != 0)
					dolzina = BR_CIFRI - i;
			cout << "Prviot broj na stepen vtoriot e ednakvo na: " << endl;
			for (int i = BR_CIFRI - dolzina; i < BR_CIFRI; i++)
				cout << broj[i];
			cout << endl << endl;
		}

        // naogjanje dali dvata broja se prosti
        if(dali_e_prost(brojA,dolzinaA))
            cout<<"Prviot broj e prost."<<endl;
        else
            cout<<"Prviot broj ne e prost."<<endl;
		if(dali_e_prost(brojB,dolzinaB))
            cout<<"Vtoriot broj e prost."<<endl;
        else
            cout<<"Vtoriot broj ne e prost."<<endl;
	}
	else
		cout << "Nastana greska pri vcituvanje na datotekite. Proverete dali istite postojat." << endl;

//	system("PAUSE");
	return 0;
}
