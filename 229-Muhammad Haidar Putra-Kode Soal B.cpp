#include<iostream>
#include<fstream>
using namespace std;

const int max_mk=10;
const int harga_sks=200000;
class MataKuliah{
	public:
	string kode,nama,hari,jam;
	int sks;
	float nilai;
	MataKuliah(){}
	MataKuliah(string k,string n,int s,string h,string j,float nl=-1){
		kode=k;
		nama=n;
		sks=s;
		hari=h;
		jam=j;
		nilai=nl;
	}
};
class Mahasiswa{
	public:
	string username,nim,nama,prodi,fakultas,metodePembayaran;
	float potonganBeasiswa;
	int jumlahKrs;
	MataKuliah krs[max_mk];
	Mahasiswa(){
		potonganBeasiswa=0;
		jumlahKrs=0;
	}
	
	void tampilkanData(){
		cout<<"Nama: "<<nama<<endl;
		cout<<"Nim: "<<nim<<endl;
		cout<<"Prodi: "<<prodi<<endl;
		cout<<"Fakultas: "<<fakultas<<endl;
	}
	void tampilkanKrs(){
		if(jumlahKrs==0){
			cout<<"Belum mengambil Mata kuliah!\n";
			return;
		}
		for(int i=0;i<jumlahKrs;i++){
			cout<<i+1<<". "<<krs[i].nama<<" ("<<krs[i].kode<<") "<<krs[i].hari<<krs[i].jam<<endl;
		}
	}
	void ambilMatkul(MataKuliah mk){
		for(int i=0;i<jumlahKrs;i++){
			if(krs[i].kode==mk.kode){
				cout<<"Mata kuliah sudah diambil sebelumnya!\n";
				return;
			}
		}
		if(jumlahKrs<max_mk){
			krs[jumlahKrs++]=mk;
			cout<<"Mata Kuliah berhasil ditambahkan!\n";
		}else{
			cout<<"KRS penuh!\n";
		}
	}
	void hapusMatkul(string kode){
		bool ditemukan=false;
		for(int i=0;i<jumlahKrs;i++){
			if(krs[i].kode==kode){
				for(int j=i;j<jumlahKrs-1;j++){
					krs[j]=krs[j+1];
				}
				jumlahKrs--;
				ditemukan=true;
				cout<<"Mata Kuliah berhasil dihapus!\n";
			}
		}
		if(!ditemukan){
			cout<<"Mata kuliah tidak ditemukan!\n";
		}
	}
	void lihatNilai(){
		for(int i=0;i<jumlahKrs;i++){
			cout<<krs[i].nama<<": ";
		if(krs[i].nilai>=0){
			cout<<krs[i].nilai<<endl;
		}else{
			cout<<"Belum ada nilai!\n";
		}
		}
	}
	void ajukanBeasiswa(float persen){
		potonganBeasiswa=persen;
		cout<<"Beasiswa "<<persen*100<< " %berhasil diajukan\n";
	}
	void pilihMetodePembayaran(){
		int pilih;
		cout<<"=========Metode Pembayaran========\n";
		cout<<"1.Transfer\n";
		cout<<"2.Tunai\n";
		cout<<"Pilih: ";
		cin>>pilih;
		
		if(pilih==1){
			metodePembayaran="Transfer";
		}else if(pilih==2){
			metodePembayaran="Tunai";
		}else{
			cout<<"Pilihan tidak valid\n";
		}
		cout<<"Metode Pembayaran "<<metodePembayaran<<" disimpan\n";
	}
	void simpanFile(){
		ofstream file("Pembayaran.txt");
		int totalSks=0;
		for(int i=0;i<jumlahKrs;i++){
			totalSks=krs[i].sks;
		}
		int total=totalSks*harga_sks;
		float diskon=total*potonganBeasiswa;
		int bayar=total-diskon;
		file<<"==========Pembayaran=======\n";
		file<<"Total Sks: "<<totalSks<<endl;
		file<<"Harga Per Sks: "<<harga_sks<<endl;
		file<<"Total biaya: "<<total<<endl;
		file<<"Potongan Beasiswa: "<<potonganBeasiswa<<endl;
		file<<"Total Bayar: "<<bayar<<endl;
		file.close();
		cout<<"Data berhasil disimpan ke 'Pembayaran.txt' \n";
	}
};

MataKuliah list[]={
MataKuliah ("A1", "Alpro", 3," Senin", " 08.00-10.00",90.0),
MataKuliah ("A2", "Arsikom", 2," Selasa", " 09.00-11.00",92.0),
MataKuliah ("A3", "Matdis", 3," Rabu", " 08.00-10.00",90.0),
MataKuliah ("A4", "Pweb", 3," Kamis", " 08.00-10.00",90.0)
};
int main(){
	Mahasiswa user;
	user.username="Haidar";
	user.nim="2400018209";
	user.nama="Muhammad Haidar Putra";
	user.prodi="Informatika";
	user.fakultas="FTI";
	
	string inputUser,inputNim;
	do{
		cout<<"======Login======\n";
		cout<<"Ussername: ";cin>>inputUser;
		cout<<"Password: ";cin>>inputNim;
		if(inputUser !=user.username || inputNim !=user.nim){
			cout<<"Login gagal.Coba Lagi\n";
		}
	}while(inputUser !=user.username || inputNim !=user.nim);
	
	int pilihan;
	do{
		cout<<"\n=======MENU=========\n";
		cout<<"1.Lihat Informasi Pribadi\n";
		cout<<"2.Ambil Mata Kuliah\n";
		cout<<"3.Hapus Mata Kuliah\n";
		cout<<"4.Lihat Jadwal\n";
		cout<<"5.Lihat Nilai\n";
		cout<<"6.Ajukan Beasiswa\n";
		cout<<"7.Metode Pembayaran\n";
		cout<<"8.Simpan Ke file\n";
		cout<<"0.keluar\n";
		cout<<"Pilih: ";
		cin>>pilihan;
		cout<<endl;
		
		switch(pilihan){
			case 1: user.tampilkanData();break;
			case 2:cout<<"====Daftar Mata Kuliah Semester 2=======\n";
			for(int i=0;i<4;i++){
				cout<<i+1<<"."<<list[i].nama<<endl;
				
			}
			int pilihMk;
			cout<<"Masukan pilihan (1-4): ";
			cin>>pilihMk;
			if(pilihMk >=1 && pilihMk <=4){
				user.ambilMatkul(list[pilihMk-1]);
			}else{
				cout<<"Pilihan tidak valid!\n";
			}
			break;
			case 3:cout<<"Masukan Mata Kuliah yang ingin dihapus (kode) : ";
			cin>>inputUser;
			user.hapusMatkul(inputUser);
			break;
			case 4:user.tampilkanKrs();
			break;
			case 5:user.lihatNilai();
			break;
			case 6:float persen;
			cout<<"Ajukan beasiswa (0.25 untuk 25% dan 0.5 untuk 50%) : ";
			cin>>persen;
			user.ajukanBeasiswa(persen);break;
			case 7:user.pilihMetodePembayaran();
			break;
			case 8:user.simpanFile();break;
			case 0:cout<<"Terimakasih Telah mengunjungi PORTAL UAD \n";
			break;
			default:cout<<"Pilihan tidak valid!\n";
		}
		
	}while(pilihan !=0);
	return 0;
}
