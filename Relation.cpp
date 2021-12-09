//
// Created by ejh61 on 2021-10-26.
//

#include "Relation.h"

void Relation::addTuple (Tuple tempTuple) {
    tuples.insert(tempTuple);
}

std::string Relation::toString() { // 구현해야함 근데 어케하는지 모르겠다 iter가 안먹힘 이유 찾아야함.
    std::ostringstream oss;

   for (Tuple t : tuples){
       oss << "  ";
       for(unsigned int i = 0; i < header.headerSize(); i++)   // tuple 과 헤더를 그 row에 맞게 반복해서 출력
           if(i != header.headerSize() - 1)
               oss << header.GetHeader().at(i) << "=" << t.getTuple().at(i) << ", ";
           else
               oss << header.GetHeader().at(i) << "=" << t.getTuple().at(i) << std::endl;
   }

   return oss.str();
}

Relation Relation::selectValue (unsigned int index, std::string value) {   // parameters are index and value, index= attribute 위치, value = 값
    Relation tempRelation(name,header); // putting the name and header in its Relation
    for (Tuple t : tuples) {
      if  (t.getTuple().at(index) == value){
          tempRelation.addTuple(t);    // value(값) equal to the value in the tuple index, store this into the new realtion
      }
    }

    return tempRelation;
}

Relation Relation::select(unsigned int index1, unsigned int index2) {   // parameters are index and index, (relation columns to select on same values)
    //똑같은 값 찾는거
    Relation tempRelation(name, header);
    for (Tuple t : tuples) {

        if (t.getTuple().at(index1) == t.getTuple().at(index2)){
            tempRelation.addTuple(t);
        }
    }
    return tempRelation;
}

Relation Relation::project ( std::vector<unsigned int> indices) {


    Header tempHeader;
    for (unsigned int i = 0; i < indices.size(); i++) {
        tempHeader.SetHeader(header.GetHeader().at(i));
    }

    Relation tempRelation (name,tempHeader);

        for (Tuple t : tuples) {
      Tuple tuple;
        for (unsigned int i = 0; i < indices.size(); i++) {
            tuple.SetTuple(t.getTuple().at(indices.at(i))); // 하나씩 입력-
        }                                 //complete tuple
        tempRelation.addTuple(tuple);    // add tuple
    }
        return tempRelation;
}

Relation Relation::rename (std::vector<std::string> attributes) {
    Header tempHeader;

    for (unsigned int i = 0; i < attributes.size(); i++) {     //creating new temp header and put the attributes in it.
        tempHeader.SetHeader(attributes.at(i));
    }

    Relation tempRelation(name, tempHeader);   // creating new Relation

    for (Tuple t : tuples) {     //튜플 일일이 복붙
        tempRelation.addTuple(t);
    }

    return tempRelation;
}

Relation Relation::naturalJoin( Relation &tempRelation) {   // joining current relation with new relation(tempRelation)

    Relation result;

    std::vector<std::pair<unsigned int, unsigned  int >> duplicatedNumbers; // colums value which will be compared.
    result.header = combineHeader(tempRelation.header, duplicatedNumbers); // attribute 업데이트

   /* if(this->tuples.size() == 0 && duplicatedNumbers.size() == 0) {
        result = tempRelation;
    }*/

        for (Tuple t: this->tuples) {    // tuples 업데이트
            for (Tuple x: tempRelation.tuples) {

                // 어떤 atribute값도 중복되지 않을경우 생각해서 해야함.
                if (duplicatedNumbers.size() == 0) { // 중복되는게 없을경우 그냥 다 때려밖는다
                    result.addTuple(combineTuples(t, x, duplicatedNumbers));
                }

                if (isJoinable(t, x, duplicatedNumbers)) {
                    result.addTuple(combineTuples(t, x, duplicatedNumbers));
                }
            }
        }


    return result;
}

Header Relation::combineHeader( Header tempHeader,std::vector<std::pair<unsigned int, unsigned int >> &tempNumbers) {
    Header result;


    for(unsigned int i = 0; i < this->header.headerSize(); i++) {
        for (unsigned int j = 0; j < tempHeader.headerSize(); j++) {

            if (this->header.GetHeader().at(i) == tempHeader.GetHeader().at(j)) {     // this->Relation 에 있는 값들을 tempHeader 에 있는 값들과(attributes) 비교해

                tempNumbers.push_back(std::make_pair(i,j));     // 페어로 만들어서 tempNumbers 에 나중에 비교해야하는 attributes 저장
            }

        }
       /* if(duplicateValue >= 0) {
            tempHeader.GetHeader().erase(tempHeader.GetHeader().begin() + duplicateValue);      // 같은 값이 나올경우 tempHeader 백터안에 있는값을 삭제
        }
        */

        result.SetHeader(this->header.GetHeader().at(i));              // 한번씩 반복해서 검증을 마칠때마다 i 번째에있는 값 새로운 result에 저장

    }



    for(unsigned int i = 0; i < tempHeader.headerSize(); i++) {    // 중복 안된 부분들 result에 저장 (만약 중복되는 부분이 없을때 통째로 다 넣음)
        int countMatch = 0;  // 중복되는 attribute 가 있는지 확인하기 위한 변수 (중복시 값증가)
        for(unsigned int j = 0 ; j < tempNumbers.size(); j++) {
            if (i == tempNumbers.at(j).second)  // 중복시
                countMatch++;                   // 값증가
        }
        if (countMatch == 0 )   // 중복이 없을시
            result.SetHeader(tempHeader.GetHeader().at(i));  // result에 추가
    }

    return result;
}

bool Relation::isJoinable (Tuple &compareTuples1,Tuple &compareTuples2,std:: vector<std::pair<unsigned  int, unsigned  int>> &tempNumbers){ // 두개의 tuples를 받고 백터안에 있는 값들에 따라서 비교를 한다
    for (unsigned int i = 0; i < tempNumbers.size(); i++) { // 두개의 튜플값이 vector안에 있는 경우의 수를 모두 충족해야 true 아닐씨 false
        if (compareTuples1.getTuple().at(tempNumbers.at(i).first) != compareTuples2.getTuple().at(tempNumbers.at(i).second)){
            return false;
        }
    }
    return true;
}

Tuple Relation::combineTuples(Tuple compareTuples1, Tuple compareTuples2, std::vector<std::pair<unsigned int, unsigned int>> &tempNumbers) {
    Tuple returnTuple;
  /*
    for (unsigned int i = 0; i < tempNumbers.size(); i++){  // 중복되는 값이 있을 경우 삭제
        compareTuples2.getTuple().erase( compareTuples2.getTuple().begin() + tempNumbers.at(i).second);
        // delete duplicate compare tuples values in 2nd one
    }
*/
    for (unsigned int i = 0; i < compareTuples1.getTuple().size(); i++) {  // 첫번째 튜플에 있는값 모두 returntuple에 저장
        returnTuple.SetTuple(compareTuples1.getTuple().at(i));
    }
    for(unsigned int i = 0; i < compareTuples2.getTuple().size(); i++) {    // 중복 안된 부분들 returntupel 에 저장 (만약 중복되는 부분이 없을때 통째로 다 넣음)
        int countMatch = 0;  // 중복되는 attribute 가 있는지 확인하기 위한 변수 (중복시 값증가)
        for(unsigned int j = 0 ; j < tempNumbers.size(); j++) {
            if (i == tempNumbers.at(j).second)  // 중복시
                countMatch++;                   // 값증가
        }
        if (countMatch == 0 )   // 중복이 없을시
            returnTuple.SetTuple(compareTuples2.getTuple().at(i));  // 값추가
    }

 /*  for (unsigned int i = 0; i < compareTuples2.getTuple().size(); i++) {
        returnTuple.SetTuple(compareTuples2.getTuple().at(i));
    }
*/
    return returnTuple;
}

void Relation::unionRelations (Relation &tempRelation) {  // tempRelation안에 있는 tuples 다 추가하고 중복은 set니 알아서 파기됨.

    for(Tuple t: tempRelation.tuples){
        this->addTuple(t);
    }
}


