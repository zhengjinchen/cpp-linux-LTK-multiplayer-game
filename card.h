struct Card{
	string name;
	int number,id;
	string Type;
	void out(){cout<<name<<"¡¾"<<dick[number]<<Type<<"¡¿";}
}a[N];

void init_Kill(){
	a[1].number=7; a[1].Type="¡ø"; a[1].id=1; a[1].name="É±";
	a[2].number=8; a[2].Type="¡ø"; a[2].id=1; a[2].name="É±";
	a[3].number=8; a[3].Type="¡ø"; a[3].id=1; a[3].name="É±";
	a[4].number=9; a[4].Type="¡ø"; a[4].id=1; a[4].name="É±";
	a[5].number=9; a[5].Type="¡ø"; a[5].id=1; a[5].name="É±";
	a[6].number=10; a[6].Type="¡ø"; a[6].id=1; a[6].name="É±";
	a[7].number=10; a[7].Type="¡ø"; a[7].id=1; a[7].name="É±";
	//-------------------
	a[8].number=10; a[8].Type="¡ñ"; a[8].id=1; a[8].name="É±";
	a[9].number=10; a[9].Type="¡ñ"; a[9].id=1; a[9].name="É±";
	a[10].number=11; a[10].Type="¡ñ"; a[10].id=1; a[10].name="É±";
	//-------------------
	a[11].number=2; a[11].Type="¡ö"; a[11].id=1; a[11].name="É±";
	a[12].number=3; a[12].Type="¡ö"; a[12].id=1; a[12].name="É±";
	a[13].number=4; a[13].Type="¡ö"; a[13].id=1; a[13].name="É±";
	a[14].number=5; a[14].Type="¡ö"; a[14].id=1; a[14].name="É±";
	a[15].number=6; a[15].Type="¡ö"; a[15].id=1; a[15].name="É±";
	a[16].number=7; a[16].Type="¡ö"; a[16].id=1; a[16].name="É±";
	a[17].number=8; a[17].Type="¡ö"; a[17].id=1; a[17].name="É±";
	a[18].number=8; a[18].Type="¡ö"; a[18].id=1; a[18].name="É±";
	a[19].number=9; a[19].Type="¡ö"; a[19].id=1; a[19].name="É±";
	a[20].number=9; a[20].Type="¡ö"; a[20].id=1; a[20].name="É±";
	a[21].number=10; a[21].Type="¡ö"; a[21].id=1; a[21].name="É±";
	a[22].number=10; a[22].Type="¡ö"; a[22].id=1; a[22].name="É±";
	a[23].number=11; a[23].Type="¡ö"; a[23].id=1; a[23].name="É±";
	a[24].number=11; a[24].Type="¡ö"; a[24].id=1; a[24].name="É±";
	//------------------
	a[25].number=6; a[25].Type="¡ô"; a[25].id=1; a[25].name="É±";
	a[26].number=7; a[26].Type="¡ô"; a[26].id=1; a[26].name="É±";
	a[27].number=8; a[27].Type="¡ô"; a[27].id=1; a[27].name="É±";
	a[28].number=9; a[28].Type="¡ô"; a[28].id=1; a[28].name="É±";
	a[29].number=10; a[29].Type="¡ô"; a[29].id=1; a[29].name="É±";
	a[30].number=13; a[30].Type="¡ô"; a[30].id=1; a[30].name="É±";
}
void init_Shan(){
	//------------------
	a[31].number=2; a[31].Type="¡ñ"; a[31].id=2; a[31].name="ÉÁ";
	a[32].number=2; a[32].Type="¡ñ"; a[32].id=2; a[32].name="ÉÁ";
	a[33].number=13; a[33].Type="¡ñ"; a[33].id=2; a[33].name="ÉÁ";
	//------------------
	//------------------
	a[34].number=2; a[34].Type="¡ô"; a[34].id=2; a[34].name="ÉÁ";
	a[35].number=2; a[35].Type="¡ô"; a[35].id=2; a[35].name="ÉÁ";
	a[36].number=3; a[36].Type="¡ô"; a[36].id=2; a[36].name="ÉÁ";
	a[37].number=4; a[37].Type="¡ô"; a[37].id=2; a[37].name="ÉÁ";
	a[38].number=5; a[38].Type="¡ô"; a[38].id=2; a[38].name="ÉÁ";
	a[39].number=6; a[39].Type="¡ô"; a[39].id=2; a[39].name="ÉÁ";
	a[40].number=7; a[40].Type="¡ô"; a[40].id=2; a[40].name="ÉÁ";
	a[41].number=8; a[41].Type="¡ô"; a[41].id=2; a[41].name="ÉÁ";
	a[42].number=9; a[42].Type="¡ô"; a[42].id=2; a[42].name="ÉÁ";
	a[43].number=10; a[43].Type="¡ô"; a[43].id=2; a[43].name="ÉÁ";
	a[44].number=11; a[44].Type="¡ô"; a[44].id=2; a[44].name="ÉÁ";
	a[45].number=11; a[45].Type="¡ô"; a[45].id=2; a[45].name="ÉÁ";
}
void init_Peach(){
	a[46].number=3; a[46].Type="¡ñ"; a[46].id=3; a[46].name="ÌÒ";
	a[47].number=4; a[47].Type="¡ñ"; a[47].id=3; a[47].name="ÌÒ";
	a[48].number=6; a[48].Type="¡ñ"; a[48].id=3; a[48].name="ÌÒ";
	a[49].number=7; a[49].Type="¡ñ"; a[49].id=3; a[49].name="ÌÒ";
	a[50].number=8; a[50].Type="¡ñ"; a[50].id=3; a[50].name="ÌÒ";
	a[51].number=9; a[51].Type="¡ñ"; a[51].id=3; a[51].name="ÌÒ";
	a[52].number=12; a[52].Type="¡ñ"; a[52].id=3; a[52].name="ÌÒ";
	//--------------------
	a[53].number=12; a[53].Type="¡ô"; a[53].id=3; a[53].name="ÌÒ";
}
void init_Jinnang(){
	a[54].number=1; a[54].Type="¡ø"; a[54].id=4; a[54].name="¾ö¶·";
	a[55].number=1; a[55].Type="¡ö"; a[55].id=4; a[55].name="¾ö¶·";
	a[56].number=1; a[56].Type="¡ô"; a[56].id=4; a[56].name="¾ö¶·";
	//----------------------------------------
	a[57].number=3; a[57].Type="¡ø"; a[57].id=5; a[57].name="¹ıºÓ";
	a[58].number=4; a[58].Type="¡ø"; a[58].id=5; a[58].name="¹ıºÓ";
	a[59].number=12; a[59].Type="¡ø"; a[59].id=5; a[59].name="¹ıºÓ";
	a[60].number=12; a[60].Type="¡ñ"; a[60].id=5; a[60].name="¹ıºÓ";
	a[61].number=3; a[61].Type="¡ö"; a[61].id=5; a[61].name="¹ıºÓ";
	a[62].number=4; a[62].Type="¡ö"; a[62].id=5; a[62].name="¹ıºÓ";
	//----------------------------------------
	a[63].number=3; a[63].Type="¡ø"; a[63].id=6; a[63].name="Ë³ÊÖ";
	a[64].number=4; a[64].Type="¡ø"; a[64].id=6; a[64].name="Ë³ÊÖ";
	a[65].number=11; a[65].Type="¡ø"; a[65].id=6; a[65].name="Ë³ÊÖ";
	a[66].number=3; a[66].Type="¡ô"; a[66].id=6; a[66].name="Ë³ÊÖ";
	a[67].number=4; a[67].Type="¡ô"; a[67].id=6; a[67].name="Ë³ÊÖ";
	//----------------------------------------
	a[68].number=7; a[68].Type="¡ñ"; a[68].id=7; a[68].name="ÎŞÖĞ";
	a[69].number=8; a[69].Type="¡ñ"; a[69].id=7; a[69].name="ÎŞÖĞ";
	a[70].number=9; a[70].Type="¡ñ"; a[70].id=7; a[70].name="ÎŞÖĞ";
	a[71].number=11; a[71].Type="¡ñ"; a[71].id=7; a[71].name="ÎŞÖĞ";
	//----------------------------------------
	a[72].number=12; a[72].Type="¡ö"; a[72].id=8; a[72].name="½èµ¶";
	a[73].number=13; a[73].Type="¡ö"; a[73].id=8; a[73].name="½èµ¶";
	//----------------------------------------
	a[74].number=11; a[74].Type="¡ø"; a[74].id=8; a[74].name="ÎŞĞ¸";
	a[75].number=13; a[75].Type="¡ø"; a[75].id=8; a[75].name="ÎŞĞ¸";
	a[76].number=1; a[76].Type="¡ñ"; a[76].id=8; a[76].name="ÎŞĞ¸";
	a[77].number=13; a[77].Type="¡ñ"; a[77].id=8; a[77].name="ÎŞĞ¸";
	a[78].number=12; a[78].Type="¡ö"; a[78].id=8; a[78].name="ÎŞĞ¸";
	a[79].number=13; a[79].Type="¡ö"; a[79].id=8; a[79].name="ÎŞĞ¸";
	a[80].number=12; a[80].Type="¡ô"; a[80].id=8; a[80].name="ÎŞĞ¸";
	//----------------------------------------
	a[81].number=7; a[81].Type="¡ø"; a[81].id=9; a[81].name="ÄÏÂù";
	a[82].number=13; a[82].Type="¡ø"; a[82].id=9; a[82].name="ÄÏÂù";
	a[83].number=7; a[83].Type="¡ö"; a[83].id=9; a[83].name="ÄÏÂù";
	//----------------------------------------
	a[84].number=1; a[84].Type="¡ñ"; a[84].id=10; a[84].name="Íò¼ı";
	//----------------------------------------
	a[85].number=1; a[85].Type="¡ñ"; a[85].id=11; a[85].name="ÌÒÔ°";
	//----------------------------------------
	a[86].number=3; a[86].Type="¡ñ"; a[86].id=12; a[86].name="Îå¹È";
	a[87].number=4; a[87].Type="¡ñ"; a[87].id=12; a[87].name="Îå¹È";
	//----------------------------------------
	a[88].number=6; a[88].Type="¡ø"; a[88].id=13; a[88].name="ÀÖ²»";
	a[89].number=6; a[89].Type="¡ñ"; a[89].id=13; a[89].name="ÀÖ²»";
	a[90].number=6; a[90].Type="¡ö"; a[90].id=13; a[90].name="ÀÖ²»";
	//----------------------------------------
	a[91].number=1; a[91].Type="¡ø"; a[91].id=14; a[91].name="ÉÁµç";
	a[92].number=12; a[92].Type="¡ñ"; a[92].id=14; a[92].name="ÉÁµç";
}
void init_Zhuangbei(){
	
}

