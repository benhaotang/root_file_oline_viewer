// RootDrawAll Function by BenhaoTang in 2021
// - Test OK with Root>=6.0 and OS!=Windows
// - Export All Canvas in One ROOT File to Certain Type
// - Export File Type can be pdf,png,jpg,tex,tiff...
void RootDrawAll(){
    TFile *file = new TFile("./upload/temp.root","read");
    ofstream outfile("./result/index.html", ios::trunc);
    outfile<<"<head><meta charset=\"utf-8\"><title>Download</title></head><body><h1>The Uploaded File Index Table</h1><hr/>"<<endl;
    for (auto&& keyAsObj : *file->GetListOfKeys()){
        auto key = (TKey*) keyAsObj;
        TTree *newtree=file->Get<TTree>(key->GetName());
        TObjArray* leaves  = newtree->GetListOfLeaves();
        Int_t nleaves = leaves->GetEntriesFast();
        outfile<<"<h2>"<<key->GetName()<<"</h2><ul>"<<endl;
        for (Int_t i = 0; i < nleaves; i++) {
            TLeaf* leaf = (TLeaf*) leaves->UncheckedAt(i);
            cout<<leaf->GetName();
            auto canvas= new TCanvas();
            char *fn;/*naming the file*/
            fn=new char[1];
            strcpy(fn,"./result/");
            strcat(fn,key->GetName());
            strcat(fn,"_");
            strcat(fn,leaf->GetName());
            strcat(fn,".pdf");
            newtree->Draw(leaf->GetName());
            canvas->Print(fn);
            outfile<<"<li><a href=\"./"<<key->GetName()<<"_"<<leaf->GetName()<<".pdf\">"<<key->GetName()<<"_"<<leaf->GetName()<<"</a></li>"<<endl;
            delete []fn;
        }
        outfile<<"</ul>"<<endl;
    }
    outfile<<"<hr/><a href=\"./all.zip\">Download All</a><hr/>Developed by Benhao Tang From Nankai University(2021)</body>"<<endl;
    outfile.close();
    exit(0);
}