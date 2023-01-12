TH2F* Deviation(const char* filename)
{
  TFile *file = new TFile(filename);
  float a,c;
  TTree *Tree = (TTree*)file->Get("TP");
  float Entries = Tree->GetEntries();
  TH2F* h = new TH2F(filename,filename, 2000, 0, 200, 10000, 0, 100);

  for (int i=0; i<Entries; i++)
    {
      Tree->GetEntry(i);
      a = Tree->GetLeaf("E_start")->GetValue();
      c = Tree->GetLeaf("PositionX")->GetValue();
      h->Fill(c-15.4,a/1000);
    }

  return h;

}
