void ADDU(int &rs, int &rt, int &rd){
  rd = rs + rt;
}
void AND(int &rs, int &rt, int &rd){
  rd = rs&rt;
}
void JR(int &jr){
  //points PC to address in jr --> use pointer?
}
void OR(int &rs, int &rt, int &rd){
  rd = rt | rs;
}
void SLTU(int &rs, int &rt, int &rd){
  rd = rs < rt;
}
