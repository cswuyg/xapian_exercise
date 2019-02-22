/***************************************************************************
*
* @file build_index.cpp
* @author cswuyg
* @date 2019/02/21
* @brief
*
**************************************************************************/
// inmemory index use deprecated class, disalbe the compile error.
#pragma warning(disable : 4996)
#include <iostream>
#include "xapian.h"

#pragma comment(lib, "libxapian.a")
#pragma comment(lib, "zdll.lib")

const char* const K_DB_PATH = "index_data";
const char* const K_DOC_UNIQUE_ID = "007";

Xapian::WritableDatabase createIndex() {
	std::cout << "--index start--" << std::endl;
	Xapian::WritableDatabase db = Xapian::InMemory::open();

	Xapian::Document doc;
	doc.add_posting("T世界", 1);
	doc.add_posting("T体育", 1);
	doc.add_posting("T比赛", 1);
	doc.set_data("世界体育比赛");
	doc.add_boolean_term(K_DOC_UNIQUE_ID);

	Xapian::docid innerId = db.replace_document(K_DOC_UNIQUE_ID, doc);

	std::cout << "add doc innerId=" << innerId << std::endl;

	db.commit();

	std::cout << "--index finish--" << std::endl;
	return db;
}

void queryIndex(Xapian::WritableDatabase db) {
	std::cout << "--search start--" << std::endl;
	Xapian::Query termOne = Xapian::Query("T世界");
	Xapian::Query termTwo = Xapian::Query("T比赛");
	Xapian::Query termThree = Xapian::Query("T体育");
	auto query = Xapian::Query(Xapian::Query::OP_OR, Xapian::Query(Xapian::Query::OP_OR, termOne, termTwo), termThree);
	std::cout << "query=" << query.get_description() << std::endl;

	Xapian::Enquire enquire(db);
	enquire.set_query(query);
	Xapian::MSet result = enquire.get_mset(0, 10);
	std::cout << "find results count=" << result.get_matches_estimated() << std::endl;

	for (auto it = result.begin(); it != result.end(); ++it) {
		Xapian::Document doc = it.get_document();
		std::string data = doc.get_data();
		Xapian::weight docScoreWeight = it.get_weight();
		Xapian::percent docScorePercent = it.get_percent();

		std::cout << "doc=" << data << ",weight=" << docScoreWeight << ",percent=" << docScorePercent << std::endl;
	}

	std::cout << "--search finish--" << std::endl;
}

int main() {
	auto db = createIndex();
	queryIndex(db);
	return 0;
}