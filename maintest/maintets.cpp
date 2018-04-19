#include <leveldb/cache.h>
#include <leveldb/comparator.h>
#include <leveldb/db.h>
#include <db/dbformat.h>
#include <iostream>
#include <sstream>

//template<typename Key, typename Value>
//class key_compare : public leveldb::Comparator
//{
//public:
//    int Compare(const leveldb::Slice& a, const leveldb::Slice& b)const
//    {
//        if(!(a.size() == sizeof(Key)) && (b.size() == sizeof(Key)));
//        Key* ak = (Key*)a.data();
//        Key* bk = (Key*)b.data();
//        if (*ak < *bk) return -1;
//        if (*ak == *bk) return 0;
//        return 1;
//    }
//
//    const char* Name()const { return "key_compare"; }
//    void FindShortestSeparator(std::string*, const leveldb::Slice&)const{}
//    void FindShortSuccessor(std::string*)const{};
//};
//



int main(int argc, char** argv) {
    namespace ldb = leveldb;


    std::string ldbPath("E:\\Github\\test\\ldb2");
    ldb::DB* dbPtr = nullptr;
    ldb::Options open_Opts;
//    open_Opts.comparator =
    open_Opts.create_if_missing = true;
    open_Opts.max_open_files = 64;
    open_Opts.compression = ldb::kNoCompression;

//create a levelDB
    auto opendb_Stat = ldb::DB::Open(open_Opts, ldbPath.c_str(), &dbPtr);
    std::cout << "DB::Open status: " << opendb_Stat.ToString() << std::endl;


//write data to level DB
    ldb::WriteOptions               write_options;
    write_options.sync = true;
    for (long i = 0; i < 1000000; i++)
    {
        std::stringstream tmpss;
        std::string       tmpstr;
        tmpss << i;
        tmpss >> tmpstr;

        ldb::Slice ks("key_" + tmpstr );
        ldb::Slice vs("value_" + tmpstr );
        //std::cout << "key: " << ks.data() << "\tvalue: " << vs.data() << std::endl;
        dbPtr->Put(write_options, ks, vs);
    }                  


//read data from leveldb



//update,delte

//destroy

    //ldb::DB::Open
    dbPtr = nullptr;
    int exit;
    std::cin >> exit;
    return 0;
}

