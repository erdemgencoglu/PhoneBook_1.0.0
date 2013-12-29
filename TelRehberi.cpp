#include <stdio.h>   //
#include <conio.h>   //Kütüphanemiz
#include <windows.h> //
#include <stdlib.h>  //

FILE *dosyaptr;
void KisiEkle();           // 
void Goruntule();          //
void Guncelle(char ad[60]);// Fonksiyon tanımlamarı
void Sil(char ad[60]);     //
void Arama();              //
int  islemDevam();
void aramayapisi(char x[60], int determ);
int telefon(char x[12]);		//

int gonder;			//tel numarası sorgulama fonksiyonu için tanımladım
char cevap, isim[30];//cevap değişkeni kullanıcadan işlem devamını almak icin kullanılmıştır.isim değişkeni sil ve guncelleiçin kullanıldı 
struct DataBase //Kişi bilgilerinin tutulduğu DataBase adındaki struct yapısı
{
	char Ad[60];			//
	char SoyAd[60];			//
	char CepTel[12];		// DataBase imizin (yani Rehberin) Uyeleri
	char EvTel[12];			//
	char IsTel[12];			//
	char Dogum_tarihi[20];	//
	char e_posta[BUFSIZ];	//
}data;
int main()
{
	system("color 1f");//Background rengini ve font rengini değiştirir.
	int secim;
	_flushall();
	system("cls");
	printf("\n\t\t\t   MENU\n\n");	//
	printf("\t\t\t ------------------------- \n");//
	printf("\t\t\t| 1. Kisi Ekle            |\n");//
	printf("\t\t\t| 2. Rehberi Goruntule    |\n");//   
	printf("\t\t\t| 3. Kisi Guncelle        |\n");// Menünün görünümü
	printf("\t\t\t| 4. Kisi Sil             |\n");//
	printf("\t\t\t| 5. Kisi Arama yap       |\n");//
	printf("\t\t\t| 6. Cikis                |\n");//
	printf("\t\t\t ------------------------- \n");//
	printf("\t\t\t Tercihiniz: ");
	scanf_s("%d", &secim);
	if (secim == 1 || secim == 2 || secim == 3 || secim == 4 || secim == 5 || secim == 6)
	{
		switch (secim)		//Kullanıcıdan hangi işlemi istediği arauldu
		{
		case 1: 	KisiEkle(); break; //Kisi ekleme fonksiyonuna gider.
		case 2:		Goruntule(); break; //Kisi gorüntüleme fonksiyonuna gider.
		case 3:	{
			do
			{
				printf("Guncellenicek ismi giriniz:");
				_flushall();//belleği temizler gets için kullanıldı
				gets(isim);
				Guncelle(isim);
				for (;;)//İşleme devam edip etmeyeceği sorgulandmıştır.
				{
					printf("\n");
					printf("Guncelleme islemine devam icin (G) \n");
					printf("Menuye donmek icin             (M) \n");
					printf("Cikis  yapmak icin             (C) \n\n");
					printf("Tercihiniz: ");
					cevap = _getche(); printf("\n"); system("cls");
					if (cevap == 'g' || cevap == 'G')
					{
						secim = 3; break;
					}
					else if (cevap == 'm' || cevap == 'M')
					{
						main(); break;
					}
					else if (cevap == 'c' || cevap == 'C')
					{
						exit(1); break;
					}
					else
						printf("\nYanlis secim yaptiniz!Lutfen belirtilen tuslari kullaniniz\n");
				}
			} while (secim = 3);
			break;
				}
		case 4:{
			do
			{
				printf("Silinecek kayit adi ? :");
				_flushall();
				gets(isim);
				Sil(isim);
				for (;;)//İşleme devam edip etmeyeceği sorgulandmıştır.
				{
					printf("\n");
					printf("Silme islemine devam icin      (S) \n");
					printf("Menuye donmek icin             (M) \n");
					printf("Cikis  yapmak icin             (C) \n\n");
					printf("Tercihiniz: ");
					scanf("%c", &cevap); system("cls");
					if (cevap == 'S' || cevap == 's')
					{
						secim = 4; break;
					}
					else if (cevap == 'm' || cevap == 'M')
					{
						main(); break;
					}
					else if (cevap == 'c' || cevap == 'C')
					{
						exit(1); break;
					}
					else
						printf("\nYanlis secim yaptiniz!Lutfen belirtilen tuslari kullaniniz\n");
				}
			} while (secim = 4);
			break;
			   }

		case 5:		Arama(); break; //Kisi arama fonksiyonuna gider.
		case 6:		exit(1); break;
		default:	printf("Lutfen belirtilen Tuslari kullaniniz");
			break;
		}
	}
	else printf("Yanlis secim yaptiniz!Tekrar Deneyiniz\n"); Sleep(1000); main();
	return 0;
}
void KisiEkle() // Kisi ekleme menüsü
{
	dosyaptr = fopen("Rehber.txt", "a");
	rewind(dosyaptr);
	if (dosyaptr == NULL){ printf("Dosya veya Surucu bulunamadi"); }//txt dosyası açılamassa bu hatayı verir.
	else
	{
		system("cls");	//Ekranı temizler
		printf("Yeni Kayit\n");
		printf("----------\n\n");					/*Kisi bilgilerinin kayıt edildiği bölüm*/
		printf("\tAd: ");						/*Kisinin Adı soruldu*/
		scanf("%s", &data.Ad);
		fprintf(dosyaptr, "%s ", data.Ad);
		printf("\tSoyad: ");						/*Kisinin Soyad bilgisi alındı*/
		scanf("%s", &data.SoyAd);
		fprintf(dosyaptr, "%s ", data.SoyAd);
		/*--------------------------CepTel icin yapılan karakter sorgulamaları-----------------------------------*/
		do
		{
			printf("\tCep Tel No: ");					 // %d yaptık ama 11 hane almıyor
			scanf("%s", &data.CepTel);
			gonder = telefon(data.CepTel);//alınan telefon numarası char tipinde telefon fonksiyonuna gönderilip sorgulanıor
		} while (gonder != 1);
		fprintf(dosyaptr, "%s ", data.CepTel);		//doğru bilgi alındıktan sonra dönen fonksiyondaki parametre yazdırılıor...
		/*--------------------------EvTel icin yapılan karakter sorgulamaları-----------------------------------*/
		do
		{
			printf("\tEv Tel No: ");
			scanf("%s", &data.EvTel);
			gonder = telefon(data.EvTel);
		} while (gonder != 1);
		fprintf(dosyaptr, "%s ", data.EvTel);
		/*--------------------------IsTel icin yapılan karakter sorgulamaları-----------------------------------*/
		do
		{
			printf("\tIs Tel No: ");
			scanf("%s", &data.IsTel);
			gonder = telefon(data.IsTel);
		} while (gonder != 1);
		fprintf(dosyaptr, "%s ", data.IsTel);
		printf("\tDogum tarihi(gg/aa/yy): ");
		scanf("%s", &data.Dogum_tarihi);
		fprintf(dosyaptr, "%s ", data.Dogum_tarihi);
		printf("\tE-posta: ");
		scanf("%s", &data.e_posta);
		fprintf(dosyaptr, "%s\t  \n", data.e_posta);
		fclose(dosyaptr); //Bilgileri aldıktan sonra dosyayı kapadık
		printf("Kisi eklendi.\n\n");
		islemDevam();
	}
}
void Goruntule()
{					// Dosya açma islemleri
	dosyaptr = fopen("Rehber.txt", "r");	//Okuma modunda açılmıştır
	int Secim;
	if (dosyaptr == NULL)//Dosya açılmassa NULL değeri gelir buna gore istenilen gerçekleştirilir
	{

		while (1)
		{
			printf("Suan rehberinizde hicbir kisi ekli degil ekleme yapmak icin (E) tusuna basiniz !");//Rehber oluşturulmamışsa bu uyarı gösterilir
			Secim = _getche(); system("cls");
			if (Secim == 'e' || Secim == 'E')
			{
				KisiEkle(); break;
			}
			else
			printf("\nYanlis secim yaptiniz!Lutfen belirtilen tuslari kullaniniz\n");
		}
	}
	else // Dosya önceden varsa kisi eklenebilir
	{
		system("cls");
		printf("Telefon Rehberi \n");
		printf("---------------\n\n");
		while (fscanf(dosyaptr, "%s%s%s%s%s%s%s", &data.Ad, &data.SoyAd, &data.CepTel, &data.EvTel, &data.IsTel, &data.Dogum_tarihi, &data.e_posta) != EOF)
		{	//Dosya sonu belirteci EOF a kadar okunur ve ekrana yazdırılır. 
			printf("Ad:\t%s\nSoyad:  %s\nCepTel: %s\nEvTel:  %s\nIsTel:  %s\nDogumT: %s\ne-posta:%s\n\n", data.Ad, data.SoyAd, data.CepTel, data.EvTel, data.IsTel, data.Dogum_tarihi, data.e_posta);
		}
		fclose(dosyaptr);//Dosya kapatıldı
		islemDevam();
	}
}
void Guncelle(char ad[60])
{
	FILE *dosyaptr, *yeni;
	int k = 0;//Kişinin rehberde olup olmadığı sorgulanmak amacı ile tanımlandı
	system("cls");
	dosyaptr = fopen("Rehber.txt", "r");//2 dosya açılmasının sebebi güncellenicek ad hariç diyer bilgiler temp bir dosyaya 
	yeni = fopen("Rehber1.txt", "w");//yazdırılır.  
	if (dosyaptr == NULL)
	{
		printf("Suan rehberinizde hicbir kisi ekli degil!");
	}
	else
	{
		rewind(dosyaptr);//dosya imlecini dosya başına alır
		rewind(yeni);
		while (!feof(dosyaptr))//dosya sonuna kadar tarama yapar
		{
			fscanf(dosyaptr, "%s %s %s %s %s %s %s ", &data.Ad, &data.SoyAd, &data.CepTel, &data.EvTel, &data.IsTel, &data.Dogum_tarihi, &data.e_posta);
			if (strcmp(data.Ad, ad) == 0)
			{
				k = 1;
				printf("\nGuncellenen Kisi Bilgiler\n");
				printf("-------------------------\n");
				printf("\tAd: ");
				scanf("%s", data.Ad);
				printf("\tSoyad: ");
				scanf("%s", data.SoyAd);
				do{
					printf("\tCep Tel No: ");
					scanf("%s", &data.CepTel);
					gonder = telefon(data.CepTel);//alınan telefon numarası char tipinde telefon fonksiyonuna gönderilip sorgulanıor
				} while (gonder != 1);
				do{
					printf("\tEv Tel No: ");
					scanf("%s", &data.EvTel);
					gonder = telefon(data.EvTel);//alınan telefon numarası char tipinde telefon fonksiyonuna gönderilip sorgulanıor
				} while (gonder != 1);
				do{
					printf("\tIs Tel No: ");
					scanf("%s", &data.IsTel);
					gonder = telefon(data.IsTel);//alınan telefon numarası char tipinde telefon fonksiyonuna gönderilip sorgulanıor
				} while (gonder != 1);
				printf("\tDogum tarihi(gg/aa/yy): ");
				scanf("%s", &data.Dogum_tarihi);
				printf("\tE-posta: ");
				scanf("%s", &data.e_posta);
				printf("\nKisi guncellendi.\n\n");
				fprintf(yeni, "%s %s %s %s %s %s %s\t  \n", data.Ad, data.SoyAd, data.CepTel, data.EvTel, data.IsTel, data.Dogum_tarihi, data.e_posta);
			}//Güncellenicek kişi dosyada tespit edilmişse yeni bilgiler alınır ve dosyaya yazdırılır eğer kişi dosyada yok ise o dosyaptr bilgiler olduğu gibi yeni dosyaya yazdırılır.	
			else
				fprintf(yeni, "%s %s %s %s %s %s %s\t  \n", data.Ad, data.SoyAd, data.CepTel, data.EvTel, data.IsTel, data.Dogum_tarihi, data.e_posta);
		}
		_fcloseall();//tüm dosyaları kapatır
		remove("Rehber.txt");//İlk txt dosyaysı silinir
		rename("Rehber1.txt", "Rehber.txt");//yeni txt dosyasının adı değiştirilir ve ilk txt dosyasının adı yapılır.
		if (k == 0)
			printf("Bu kisi rehberde kayitli degildir...\n"); Sleep(500);
	}
}
void Sil(char ad[60])
{
	system("cls");
	FILE *dosyaptr, *yeni;
	int a = 0;
	dosyaptr = fopen("Rehber.txt", "r");//okuma modunda açıldı
	yeni = fopen("Rehber1.txt", "w");//yazma modunda açıldı
	if (dosyaptr == NULL)
	{
		printf("Suan rehberinizde hicbir kisi ekli degil!");
	}
	else
	{
		rewind(dosyaptr);
		rewind(yeni);
		printf("\n%s Kisisini silmek istiyormusunuz! (E)-(H)\n", isim);//kişi  uyarıldı
		cevap = _getch();
		if (cevap == 'E' || cevap == 'e')
		{
			while (!feof(dosyaptr))//dosya sonuna kadar okutuldu ve dosyaptr dosyadan bilgiler alındı
			{
				fscanf(dosyaptr, "%s %s %s %s %s %s %s ", &data.Ad, &data.SoyAd, &data.CepTel, &data.EvTel, &data.IsTel, &data.Dogum_tarihi, &data.e_posta);
				if (!strcmp(data.Ad, ad))//Dosyadaki tüm adları tarar ve girilen isim ile eşitse bu kısıma girer ve bu kişi hariç diğer kişileri yeni dosyaya yazar böylece kişi silinmiş olur.
				{
					printf("\nSilinen Kisi Bilgileri\n");
					printf("------------------------\n");
					printf("Ad:\t%s\nSoyad:  %s\nCepTel: %s\nEvTel:  %s\nIsTel:  %s\nDogumT: %s\ne-posta:%s\n\n", data.Ad, data.SoyAd, data.CepTel, data.EvTel, data.IsTel, data.Dogum_tarihi, data.e_posta);
					printf("\nKisi silindi..."); Sleep(500);
					a = 1;
				}
				else//bu kısımada kişi yoksa girer böylece tüm dosyaptr bilgiler değiştirilmeden yeni metin belgesine yazdırılmış olur
					fprintf(yeni, "%s %s %s %s %s %s %s\t  \n", data.Ad, data.SoyAd, data.CepTel, data.EvTel, data.IsTel, data.Dogum_tarihi, data.e_posta);
			}
			_fcloseall();//Tüm dosyalar kapatıldı
			remove("Rehber.txt");//Rehber.txt dosyası silindi	
			rename("Rehber1.txt", "Rehber.txt");//Yeni açılan Rehber1 dosyası Rehber olarak yeniden adlandırıldı
			if (a == 0)
				printf("\nBu kisi rehberde kayitli degil!\n");
		}
		else if (cevap == 'h' || cevap == 'H')
		{	printf("Menuye donuluyor...."); Sleep(1000); main();}
		else { printf("Yanlis tus kombinasyonu!\n"); printf("Menuye donuluyor...."); Sleep(1000); main(); };
	}
}
void Arama()
{
	char isim[30], determ;
	int Secim, flag = 0;
	dosyaptr = fopen("Rehber.txt", "r");
	if (dosyaptr == NULL)
	{
		printf("Dosya veya sunucu bulunamadi!\n"); Sleep(1000);
	}
	else
	{
		system("cls");
		printf("1-Ad ile arama\n");
		printf("2-SoyAd ile arama\n");
		printf("3-e-posta ile arama\n");
		scanf("%d", &Secim);
		switch (Secim)
		{
		case 1:// Ad ile sorgulama 
			{
				printf("Aranan kisinin adini giriniz:");
				_flushall();
				gets(isim); printf("\n"); // scanf ile almıyor burda gets ile alıyor 
				determ = 0;
				aramayapisi(isim, determ);
				break;
			   }
		case 2:
			{
				printf("Aranan kisinin soyadini giriniz:");
				_flushall();
				gets(isim); printf("%s\n", isim); // scanf ile almıyor burda gets ile alıyor 
				determ = 1;
				aramayapisi(isim, determ);//arama yapısı fonksiyonuna gider ve determ parametresi burada admı 1 olduğu için soyad araması yapar.
				break;
			  }
		case 3:
			{
				printf("Aranan kisinin eposta adresini giriniz:");
				_flushall();
				gets(isim); printf("%s\n", isim); // scanf ile almıyor burda gets ile alıyor 
				determ = 2;
				aramayapisi(isim, determ);
				break;
			  }
		}
		islemDevam();
	}
}
int telefon(char x[12])//sorgu fonksiyonu
{
	int flag = 0, dogru = 0, yanlis = 1;
	if (x[11] != NULL || x[10] == NULL || x[9] == NULL || x[8] == NULL || x[7] == NULL || x[6] == NULL || x[5] == NULL || x[4] == NULL || x[3] == NULL || x[2] == NULL || x[1] == NULL)
	{
		printf("Telefon numaraniz 11 haneli ve 0-9 arasi rakam icermelidir!\n");  Sleep(1000); return dogru;
	}
	for (int i = 0; data.CepTel[i] != '\0'; i++)//karakter girip girmediği kontrol edildi
	{
		if (x[i] != '1' && x[i] != '2' && x[i] != '3' && x[i] != '4' && x[i] != '5' && x[i] != '6' && x[i] != '7' && x[i] != '8' && x[i] != '9' && x[i] != '0')
		{
			flag = 1;
		}
		else flag = 0;
	}
	if (flag == 1)//flag 1 ise karakter girilmiş demektir.
	{
		printf("Lutfen 0 ile 9 arasinda rakam kullaniniz!\n"); Sleep(1000); return dogru;
	}
	else return yanlis;
}
void aramayapisi(char x[60], int determ)
{
	system("cls");
	int flag = 0;
	rewind(dosyaptr);
	while (fscanf(dosyaptr, "%s", &data.Ad) != EOF) //Dosyada bulunan adları EOF a kadar okur
	{
		fscanf(dosyaptr, "%s", &data.SoyAd);		// 
		fscanf(dosyaptr, "%s", &data.CepTel);		//
		fscanf(dosyaptr, "%s", &data.EvTel);		//Dosyadan okunan diyer bilgiler
		fscanf(dosyaptr, "%s", &data.IsTel);		//
		fscanf(dosyaptr, "%s", &data.Dogum_tarihi);	//
		fscanf(dosyaptr, "%s", &data.e_posta);		//
		if (determ == 0)//determine kişiyinin hangi şekilde arama yapmak istediğini anlar.
		{
			if (!strcmp(data.Ad, x))//Aranan isimle Karşılaştırma yapılır doğruysa ekrana yazıdırılır 
			{
				printf("Kisi Bilgileri\n");
				printf("--------------\n");
				printf("Ad:\t%s\nSoyad:  %s\nCepTel: %s\nEvTel:  %s\nIsTel:  %s\nDogumT: %s\ne-posta:%s\n\n", data.Ad, data.SoyAd, data.CepTel, data.EvTel, data.IsTel, data.Dogum_tarihi, data.e_posta);
				flag = 1;
			}
		}
		if (determ == 1)
		{
			if (!strcmp(data.SoyAd, x))//Aranan isimle Karşılaştırma yapılır doğruysa ekrana yazıdırılır 
			{
				printf("Kisi Bilgileri\n");
				printf("--------------\n");
				printf("Ad:\t%s\nSoyad:  %s\nCepTel: %s\nEvTel:  %s\nIsTel:  %s\nDogumT: %s\ne-posta:%s\n\n", data.Ad, data.SoyAd, data.CepTel, data.EvTel, data.IsTel, data.Dogum_tarihi, data.e_posta);
				flag = 1;
			}
		}
		if (determ == 2)
		{
			if (!strcmp(data.e_posta, x))//Aranan isimle Karşılaştırma yapılır doğruysa ekrana yazıdırılır 
			{
				printf("Kisi Bilgileri\n");
				printf("--------------\n");
				printf("Ad:\t%s\nSoyad:  %s\nCepTel: %s\nEvTel:  %s\nIsTel:  %s\nDogumT: %s\ne-posta:%s\n\n", data.Ad, data.SoyAd, data.CepTel, data.EvTel, data.IsTel, data.Dogum_tarihi, data.e_posta);
				flag = 1;
			}
		}
	}
	if (flag == 0)
	{
		printf("\nBu kisi rehberde kayitli degil!\n\n");
	}
}
int islemDevam()
{
	while (1)//İşleme devam edip etmeyeceği sorgulandmıştır.
	{
		printf("Yeni bir kisi eklemek icin    (E)\n");
		printf("Menuye donmek icin            (M)\n");
		printf("Arama yapmak icin             (A)\n");
		printf("Rehber goruntulemesi icin     (G)\n");
		printf("Cikis  yapmak icin            (C)\n\n");
		printf("Tercihiniz: ");
		cevap = _getche(); system("cls");
		if (cevap == 'e' || cevap == 'E')
		{
			KisiEkle(); break;
		}
		else if (cevap == 'm' || cevap == 'M')
		{
			main(); break;
		}
		else if (cevap == 'g' || cevap == 'G')
		{
			Goruntule(); break;
		}
		else if (cevap == 'a' || cevap == 'A')
		{
			Arama(); break;
		}
		else if (cevap == 'c' || cevap == 'C')
		{
			exit(1); break; //program penceresini kapatır
		}
		else printf("\nYanlis secim yaptiniz!Lutfen belirtilen tuslari kullaniniz\n");
	}return 0;
}

