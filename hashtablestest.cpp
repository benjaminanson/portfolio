#include "hashtable.hpp"
#include <string>
#include <chrono>

using std::string;
using std::stoi;

//This helps with testing, do not modify.
template <typename Type>
string NumberToString(Type Number)
{
  stringstream ss;
  ss << Number;
  return ss.str();
}

template <typename T>
bool checkTest(int testNum, int& correct, T whatItShouldBe, T whatItIs) {

  if (whatItShouldBe == whatItIs) {
    correct++;
    cout << "Passed " << testNum << endl;
    return true;
  }
  else {

    cout << "***Failed test " << testNum << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been " << whatItShouldBe << endl;
    cout << "The unit test checker is closing down the program now due to a failed test" << endl;
    exit(1);
    return false;
  }
}

//This helps with testing, do not modify the code.
bool checkTest(int testNum, int& correct, const string& whatItShouldBe, const string& whatItIs) {

  if (whatItShouldBe == whatItIs) {
    correct++;
    cout << "Passed " << testNum << endl;
    return true;
  }
  else {
    if (whatItShouldBe == "") {
      cout << "***Failed test " << testNum << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been blank. " << endl;
    }
    else {
      cout << "***Failed test " << testNum << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been " << whatItShouldBe << endl;
    }
    cout << "The unit test checker is closing down the program now due to a failed test" << endl;
    exit(1);
    return false;
  }
}

template <typename T>
bool checkTestExistsKey(int testNum, int& correct, const T& key, bool whatItShouldBe, bool whatItIs) {
  if (whatItShouldBe == whatItIs) {
    correct++;
    cout << "Passed " << testNum << endl;
    return true;
  }
  else {

    if (whatItShouldBe) {
      cout << "***Failed test " << testNum << " *** " << endl << "This test should have found an item with key \"" << key << "\", This test did NOT find an item with key \"" << key << "\"" << endl;
    }
    else {
      cout << "***Failed test " << testNum << " *** " << endl << "This test should NOT have found an item with key \"" << key << "\", This test found an item with key \"" << key << "\"" << endl;
    }
    cout << "The unit test checker is closing down the program now due to a failed test" << endl;
    exit(1);
    return false;
  }
}

bool checkTestCluster(int testNum, int& correct, unsigned int maxWhatItShouldBe, unsigned int whatItIs) {
  if (whatItIs <= maxWhatItShouldBe ) {
    correct++;
    cout << "Passed " << testNum << ". Your worst cluster was " << whatItIs << " items." << endl;
    return true;
  }
  else {

    cout << "***Failed " << testNum << " *** " << endl << " A cluster exists of " << whatItIs << " consecutive items, it shouldn't be worse than " << maxWhatItShouldBe << endl;

    cout << "The unit test checker is closing down the program now due to a failed test" << endl;
    exit(1);
    return false;
  }
}

bool checkTestMatch(int testNum, int& correct, int value1, int value2) {
  if (value1 == value2 ) {
    correct++;
    cout << "Passed " << testNum << endl;
    return true;
  }
  else {
    cout << "***Failed " << testNum << " *** " << endl << " The two values didn't match. value1: " << value1 << " value2 " << value2 << endl;

    cout << "The unit test checker is closing down the program now due to a failed test" << endl;
    exit(1);
    return false;
  }
}

bool checkTestSimilar(int testNum, int& correct, double time1, double time2, double percentage) {
  double computedPercent = (time2 - time1)/time1 * 100;

  if (abs(computedPercent) < abs(percentage)) {
    correct++;
    cout << "Passed " << testNum << ". The quadratic probing time was " << computedPercent << "% better than the linear probing time." << endl;
    return true;
  }
  else {

    cout << "***Failed " << testNum << " *** " << endl << "The two times differed by more than " << percentage << "%." << endl;

    cout << "The unit test checker is closing down the program now due to a failed test" << endl;
    exit(1);
    return false;
  }
}


//************************************************************
//A quick and simple class that simulates a Product object.
//************************************************************
class Product {
public:
  void setCost(int cost);
  void setName(const string&);
  string getName();
  int getCost();
  string getAllInfo();
private:
  string name;
  int cost{ 0 };
};
void Product::setCost(int cost) {
  this->cost = cost;
}
void Product::setName(const string& name) {
  this->name = name;
}
string Product::getName() {
  return name;
}
int Product::getCost() {
  return cost;
}
string Product::getAllInfo() {
  stringstream ss;
  ss << "Name: " << name << ", Cost: " << cost;
  return ss.str();
}

//This helps with testing, do not modify.
bool testLinearProber() {

  int testNum = 1;
  int correct = 0;
  cout << "--------testLinearProber Tests--------" << endl;
  
  LinearProber<int> linearProber;
  linearProber.loadNumSlots(1000);
  linearProber.hashTheKey(12345);
  int currSlot = linearProber.computeSlot();
  checkTest(testNum++, correct, currSlot, currSlot); // 1
  checkTest(testNum++, correct, (currSlot+1) % 1000, linearProber.computeSlot()); // 2
  checkTest(testNum++, correct, (currSlot+2) % 1000, linearProber.computeSlot()); // 3
  checkTest(testNum++, correct, (currSlot+3) % 1000, linearProber.computeSlot()); // 4
  checkTest(testNum++, correct, (currSlot+4) % 1000, linearProber.computeSlot()); // 5

  for (int i = 0; i < 995; i++) {
    linearProber.computeSlot();
  }
  checkTest(testNum++, correct, (currSlot+1000) % 1000, linearProber.computeSlot()); // 6
  checkTest(testNum++, correct, (currSlot+1001) % 1000, linearProber.computeSlot()); // 7
  
  return (testNum - 1 == correct && correct > 0);
}

bool testQuadraticProber() {

  int testNum = 1;
  int correct = 0;
  cout << "--------testQuadraticProber Tests--------" << endl;
  QuadraticProber<int> quadraticProber;
  const int N = 1024;
  quadraticProber.loadNumSlots(N);
  quadraticProber.hashTheKey(12345);
  int currSlot = quadraticProber.computeSlot();
  checkTest(testNum++, correct, currSlot, currSlot); // 1
  checkTest(testNum++, correct, ((currSlot+1) + N) % N, quadraticProber.computeSlot()); // 2
  checkTest(testNum++, correct, ((currSlot+3) + N) % N, quadraticProber.computeSlot()); // 3
  checkTest(testNum++, correct, ((currSlot+6) + N) % N, quadraticProber.computeSlot()); // 4
  checkTest(testNum++, correct, ((currSlot+10) + N) % N, quadraticProber.computeSlot()); // 5

  for (int i = 0; i < 990; i++) {
    quadraticProber.computeSlot();
  }

  checkTest(testNum++, correct, (((currSlot+(995 + 995*995)/2) % N)), quadraticProber.computeSlot()); // 6
  checkTest(testNum++, correct, (((currSlot+(996 + 996*996)/2) % N)), quadraticProber.computeSlot()); // 7
  
  return (testNum - 1 == correct && correct > 0);
}

bool testSimpleHash() {

  int testNum = 1;
  int correct = 0;
  cout << "--------testSimpleHash Tests--------" << endl;

  HashTable<string, string> myHash("linear");

  // Add "Monster Mash" into our hash with a key of 619238.  Try to retrieve it.
  string myString = "Monster Mash";

  myHash.create("619238", myString);

  checkTest(testNum++, correct, "Monster Mash", myHash.retrieve("619238")); // 1

  // Attempt to get the Monster Mash using the operator[] code.
  checkTest(testNum++, correct, "Monster Mash", myHash["619238"]); // 2

  // Attempt to change the value at this location:
  myHash["619238"] = "Graveyard Smash";

  checkTest(testNum++, correct, "Graveyard Smash", myHash["619238"]); // 3

  // See if we can find it
  checkTestExistsKey(testNum++, correct, "619238", true, myHash.exists("619238")); // 4

  // See if we can find something that doesn't exist yet.
  checkTestExistsKey(testNum++, correct, "1234", false, myHash.exists("1234")); // 5

  // Removing it from the hash
  myHash.remove("619238");
  checkTestExistsKey(testNum++, correct, "619238", false, myHash.exists("619238")); // 6

  // Add add in "The Monster Hash" values.  
  myHash.create("13", "flash");
  myHash.create("25", "vampires feast");
  myHash.create("101", "humble abodes");
  myHash.create("77", "Transylvania Twist");
  myHash.create("12", "zombies");
  myHash.create("42", "Wolfman");
  myHash.create("97", "Dracula");
  myHash.create("123", "Dracula's son");
  myHash.create("500", "coffin-bangers");

  // Attempt to retrieve some
  checkTest(testNum++, correct, "zombies", myHash.retrieve("12")); // 7
  checkTest(testNum++, correct, "Transylvania Twist", myHash.retrieve("77")); // 8
  checkTest(testNum++, correct, "Dracula's son", myHash.retrieve("123")); // 9

  // Now count up how many are in there
  checkTest(testNum++, correct, 9, myHash.getTotalCount()); // 10

  // Now just verify that they aren't clustering up badly.
  checkTestCluster(testNum++, correct, 7u, myHash.getWorstCluster()); // 11

  return (testNum - 1 == correct && correct > 0);
}

bool testHashOfObjects() {

  int testNum = 1;
  int correct = 0;
  cout << "--------testHashOfObjects Tests--------" << endl;

  HashTable<string, Product> myHash ("linear");

  // Add in a studentObject. Try to retrive it.
  Product tempProduct;
  tempProduct.setCost(5);
  tempProduct.setName("Silly string");
  myHash.create("12341-51231", tempProduct);
  checkTest(testNum++, correct, "Silly string", myHash.retrieve("12341-51231").getName()); // 1

  // Attempt to get the product using its ID code
  checkTest(testNum++, correct, "Silly string", myHash["12341-51231"].getName()); // 2

  // See what happens if two products have the same ID code. This should overwrite the former.
  tempProduct.setCost(18);
  tempProduct.setName("Novelty foam hat");
  myHash["12341-51231"] = tempProduct;
  checkTest(testNum++, correct, "Novelty foam hat", myHash["12341-51231"].getName()); // 3

  // See if we can find it
  checkTestExistsKey(testNum++, correct, "12341-51231", true, myHash.exists("12341-51231")); // 4

  // See if we can find something that doesn't exist yet.
  checkTestExistsKey(testNum++, correct, "56756-75675", false, myHash.exists("56756-75675")); // 5

  // Remove it from the hash
  myHash.remove("12341-51231");
  checkTestExistsKey(testNum++, correct, "12341-51231", false, myHash.exists("12341-51231")); // 6

  return (testNum - 1 == correct && correct > 0);

}

//This helps with testing, do not modify.
bool testManyItems() {

  int testNum = 1;
  int correct = 0;
  cout << "--------testManyItems Tests--------" << endl;

  HashTable<int, string> myHash(2097152, "linear");

  // Place 1000000 items into the hash table.
  int key = 0;
  stringstream out;
  for (unsigned int i = 0; i < 1000000; i++) {

    // This next part just helps create some variation in keys
    if (i % 2 == 0) {
      key += 17;
    }
    else if (i % 3 == 0) {
      key += 23;
    }
    else if (i % 5 == 0) {
      key += 51;
    }
    else if (i % 7 == 0) {
      key += 13;
    }
    else {
      key += 71;
    }
    out.str("");
    out << "a-" << i;
    string value = out.str();
    myHash.create(key, value); //Just add a bunch of letter a's
  }

  //Make sure they all go in there. 
  checkTest(testNum++, correct, 1000000, myHash.getTotalCount()); // 1

  //Verify one of the values in the hash table.
  checkTest(testNum++, correct, "a-2345", myHash.retrieve(76154)); // 2

  checkTestCluster(testNum++, correct, 4000, myHash.getWorstCluster()); // 3

  //Remove the key "184275".
  myHash.remove(184275);
  checkTestExistsKey(testNum++, correct, 184275, false, myHash.exists(184275)); // 4

  //There should be one less value now
  checkTest(testNum++, correct, (1000000 - 1), myHash.getTotalCount()); // 5

  return (testNum - 1 == correct && correct > 0);
}


bool testSimpleHashQuadratic() {

  int testNum = 1;
  int correct = 0;
  cout << "--------testSimpleHashQuadratic Tests--------" << endl;

  HashTable<string, string> myHash("quadratic");

  // Add "Monster Mash" into our hash with a key of 619238.  Try to retrieve it.
  string myString = "Monster Mash";

  myHash.create("619238", myString);

  checkTest(testNum++, correct, "Monster Mash", myHash.retrieve("619238")); // 1

  // Attempt to get the Monster Mash using the operator[] code.
  checkTest(testNum++, correct, "Monster Mash", myHash["619238"]); // 2

  // Attempt to change the value at this location:
  myHash["619238"] = "Graveyard Smash";

  checkTest(testNum++, correct, "Graveyard Smash", myHash["619238"]); // 3

  // See if we can find it
  checkTestExistsKey(testNum++, correct, "619238", true, myHash.exists("619238")); // 4

  // See if we can find something that doesn't exist yet.
  checkTestExistsKey(testNum++, correct, "1234", false, myHash.exists("1234")); // 5

  // Removing it from the hash
  myHash.remove("619238");
  checkTestExistsKey(testNum++, correct, "619238", false, myHash.exists("619238")); // 6

  // Add add in "The Monster Hash" values.  
  myHash.create("13", "flash");
  myHash.create("25", "vampires feast");
  myHash.create("101", "humble abodes");
  myHash.create("77", "Transylvania Twist");
  myHash.create("12", "zombies");
  myHash.create("42", "Wolfman");
  myHash.create("97", "Dracula");
  myHash.create("123", "Dracula's son");
  myHash.create("500", "coffin-bangers");

  // Attempt to retrieve some
  checkTest(testNum++, correct, "zombies", myHash.retrieve("12")); // 7
  checkTest(testNum++, correct, "Transylvania Twist", myHash.retrieve("77")); // 8
  checkTest(testNum++, correct, "Dracula's son", myHash.retrieve("123")); // 9

  // Now count up how many are in there
  checkTest(testNum++, correct, 9, myHash.getTotalCount()); // 10

  // Now just verify that they aren't clustering up badly.
  checkTestCluster(testNum++, correct, 7u, myHash.getWorstCluster()); // 11

  return (testNum - 1 == correct && correct > 0);
}


//This helps with testing, do not modify.
bool testManyItemsQuadratic() {

  int testNum = 1;
  int correct = 0;
  cout << "--------testManyItemsQuadratic Tests--------" << endl;

  HashTable<int, string> myHash(2097152, "quadratic");

  // Place 1000000 items into the hash table.
  int key = 0;
  stringstream out;
  for (unsigned int i = 0; i < 1000000; i++) {

    // This next part just helps create some variation in keys
    if (i % 2 == 0) {
      key += 17;
    }
    else if (i % 3 == 0) {
      key += 23;
    }
    else if (i % 5 == 0) {
      key += 51;
    }
    else if (i % 7 == 0) {
      key += 13;
    }
    else {
      key += 71;
    }
    out.str("");
    out << "a-" << i;
    string value = out.str();
    myHash.create(key, value); //Just add a bunch of letter a's
  }

  //Make sure they all go in there. 
  checkTest(testNum++, correct, 1000000, myHash.getTotalCount()); // 1

  //Verify one of the values in the hash table.
  checkTest(testNum++, correct, "a-2345", myHash.retrieve(76154)); // 2

  checkTestCluster(testNum++, correct, 4000, myHash.getWorstCluster()); // 3

  //Remove the key "184275".
  myHash.remove(184275);
  checkTestExistsKey(testNum++, correct, 184275, false, myHash.exists(184275)); // 4

  //There should be one less value now
  checkTest(testNum++, correct, (1000000 - 1), myHash.getTotalCount()); // 5

  return (testNum - 1 == correct && correct > 0);
}

//This helps with testing, do not modify.
bool testCompareLinearQuadratic() {

  int testNum = 1;
  int correct = 0;
  cout << "--------testCompareLinearQuadratic Tests--------" << endl;

  HashTable<int, int> linearHash(67'108'864, "linear");
  HashTable<int, int> quadraticHash(67'108'864, "quadratic");

  // Place 1000000 items into the hash table.
  int key = 0;
  stringstream out;
  cout << "Entering values" << endl;
  for (unsigned int i = 0; i < 61'000'000; i++) {
    linearHash.create(i,i);
    quadraticHash.create(i,i);
  }
  cout << "Finished values" << endl;
  // Set up a timer
  int linearValues{0};
  auto start = std::chrono::high_resolution_clock::now();
  for (unsigned int i = 0; i < 61'000'000; i++) {
    linearValues += linearHash[i];
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::micro> diff = end - start;
  double linearTime = diff.count() / 1000.0;

  int quadraticValues{0};
  start = std::chrono::high_resolution_clock::now();
  for (unsigned int i = 0; i < 61'000'000; i++) {
    quadraticValues += linearHash[i];
  }
  end = std::chrono::high_resolution_clock::now();
  diff = end - start;
  double quadraticTime = diff.count() / 1000.0;
  checkTestMatch(testNum++, correct, 1741251424, linearValues); // 1
  checkTestMatch(testNum++, correct, linearValues, quadraticValues); // 2
  cout << "The linear probing hash table took: " << linearTime << " milliseconds to look up all values." << endl;
  cout << "The quadratic probing hash table took: " << quadraticTime << " milliseconds to look up all values." << endl;
  
  checkTestSimilar(testNum++, correct, quadraticTime, linearTime, 15.0); // 3
  return (testNum - 1 == correct && correct > 0);
}


int main(int argc, char** argv) {

  int test = 0;
  int count = 0;

  if (argc > 1) {
    test = stoi(argv[1]);
  }
  switch (test) {
    case 0:
      if (testLinearProber()) count++;
      if (testSimpleHash()) count++;
      if (testHashOfObjects()) count++;
      if (testManyItems()) count++;
      if (testQuadraticProber()) count++;
      if (testSimpleHashQuadratic()) count++;
      if (testManyItemsQuadratic()) count++;
      if (testCompareLinearQuadratic()) count++;

      cout << "----------------" << endl;
      cout << "Passed " << count << " out of 8 group tests" << endl;
      cout << "--End of tests--" << endl;
      return count != 8;
    case 1:
      return !testLinearProber();
    case 2:
      return !testSimpleHash();
    case 3:
      return !testHashOfObjects();
    case 4:
      return !testManyItems();
    case 5:
      return !testQuadraticProber();
    case 6:
      return !testSimpleHashQuadratic();
    case 7:
      return !testManyItemsQuadratic();
    case 8:
      return !testCompareLinearQuadratic();    
  }
}