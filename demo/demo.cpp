#include <leveldb/db.h>
#include <iostream>
#include <sstream>

#include <algorithm>
#include <functional>
#include <cctype>

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::transform;
using std::ptr_fun;


int main(int argc, char** argv) {
    namespace ldb = leveldb;

    string ldbPath1("E:\\Github\\test\\ldb1");
    string ldbPath2("E:\\Github\\test\\ldb2");
    string ldbPath3("E:\\Github\\test\\ldb3");
    ldb::DB* dbPtr1 = nullptr;
    ldb::DB* dbPtr2 = nullptr;
    ldb::Options open_Opts;
//  open_Opts.comparator =
    open_Opts.create_if_missing = true;
    //open_Opts.error_if_exists = true;

    open_Opts.max_open_files = 64;
    open_Opts.compression = ldb::kNoCompression;

    //create/open a levelDB
    auto opendb_Stat = ldb::DB::Open(open_Opts, ldbPath1.c_str(), &dbPtr1);
    if (opendb_Stat.ok())
    {
        cout << "DB::Open status: " << opendb_Stat.ToString() << endl;
    }
    else
    {
        cerr << opendb_Stat.ToString() << endl;
    }

    //write data to level DB
    ldb::WriteOptions               write_options;
    write_options.sync = true;
    for (long i = 0; i < 10000; i++)
    {
        stringstream tmpss;
        string       tmpstr;
        tmpss << i;
        tmpss >> tmpstr;

        string keystr = "key_" + tmpstr;
        ldb::Slice ks( keystr );
        ldb::Slice vs( "value_" + tmpstr );
        //cout << "key: " << ks.data() << "\tvalue: " << vs.data() << endl;
        dbPtr1->Put(write_options, ks, vs);
    }                  

    //read data from leveldb
    ldb::ReadOptions              read_option1;
    string                        key_to_read = "key_9999";
    string                        value_read;
    //read_option1.snapshot = dbPtr1->GetSnapshot();
    auto read_state = dbPtr1->Get(read_option1, key_to_read, &value_read);
    cout << "read state: " << read_state.ToString() << endl;
    cout << "read value: " << value_read  << endl;

    //update
    auto update_state = dbPtr1->Put(write_options, "key_8888", "updated_value_8888");
    string                        value_update;
    cout << "update state: " << update_state.ToString() << endl;
    auto get_state = dbPtr1->Get(read_option1, "key_8888", &value_update);
    cout << "get state: " << get_state.ToString() << endl;
    cout << "updated value: " << value_update << endl;

    //delete
    string value_del = "";
    auto del_state = dbPtr1->Delete(write_options, "key_4444");
    cout << "Delete state: " << del_state.ToString() << endl;
    dbPtr1->Get(read_option1, "key_4444", &value_del);
    cout << "Delete value: " << value_del << endl;



    ldb::Iterator * iter = dbPtr1->NewIterator(read_option1);
    iter->SeekToFirst();
    if ( iter->Valid() )
    {
        cout << "first key: " << iter->key().ToString() << "first value: " << iter->value().ToString() << endl;
    }

    iter->Seek("key_5555");
    if ( iter->Valid() )
    {
        cout << "key_5555 key: " << iter->key().ToString() << "key_5555 value: " << iter->value().ToString() << endl;
    }


    ldb::Iterator * itr = dbPtr1->NewIterator(read_option1);
    for (itr->SeekToFirst(); itr->Valid(); itr->Next())
    {
        cout << "key: " << itr->key().ToString() << "     value: " << itr->value().ToString() << endl;

    }

    //destroy
    //ldb::DestroyDB( ldbPath1,open_Opts );
    //ldb::DB::Open
    dbPtr1 = nullptr;
    int exit;
    std::cin >> exit;
    return 0;
}

