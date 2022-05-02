#include "gtest_lite.h"

#include "entity.h"

using namespace factolog;

class EntityDummy : public Entity {
    public:
    EntityDummy():Entity("DUMMY",12){}
    std::string toBlueprint() const {return "DUMMY";}
};

void entity_test(){
    TEST(Entity, ConnectionString){
        EntityDummy dummy;

        std::string s = dummy.getConnectionString();

        EXPECT_STREQ("\"connections\":{\"1\":{\"red\":[],\"green\":[]},\"2\":{\"red\":[],\"green\":[]}}", s.c_str());
    }END;
    TEST(Entity, OneConnection){
        EntityDummy dummy;

        dummy.addIncomingConnection(2);

        std::string s = dummy.getConnectionString();

        EXPECT_STREQ("\"connections\":{\"1\":{\"red\":[{\"entity_id\":2,\"circuit_id\":2}],\"green\":[]},\"2\":{\"red\":[],\"green\":[]}}", s.c_str());
    }END;
    TEST(Entity, OneGreenConnection){
        EntityDummy dummy;

        dummy.addIncomingConnection(2, false);

        std::string s = dummy.getConnectionString();

        EXPECT_STREQ("\"connections\":{\"1\":{\"red\":[],\"green\":[{\"entity_id\":2,\"circuit_id\":2}]},\"2\":{\"red\":[],\"green\":[]}}", s.c_str());
    }END;
    TEST(Entity, OneConnectionOut){
        EntityDummy dummy;

        dummy.addOutgoingConnection(2);

        std::string s = dummy.getConnectionString();

        EXPECT_STREQ("\"connections\":{\"1\":{\"red\":[],\"green\":[]},\"2\":{\"red\":[{\"entity_id\":2,\"circuit_id\":1}],\"green\":[]}}", s.c_str());
    }END;
    TEST(Entity, OneGreenConnection){
        EntityDummy dummy;

        dummy.addOutgoingConnection(2, false);

        std::string s = dummy.getConnectionString();

        EXPECT_STREQ("\"connections\":{\"1\":{\"red\":[],\"green\":[]},\"2\":{\"red\":[],\"green\":[{\"entity_id\":2,\"circuit_id\":1}]}}", s.c_str());
    }END;
}
