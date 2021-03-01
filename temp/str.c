struct client {
    char * name;
    char *address;
    long country_code;
    long telephone;
};


int main () {
    {
        struct client new_client;
        new_client.name = "John";
        new_client.address = "123 adsf";
        new_client.country_code = 65;
        new_client.telephone =  12345135;
    }
    {
        struct client new_client;
        long a = new_client.telephone;
    }
    /*{*/
        /*struct client new_client = {*/
            /*.name = "John";*/
            /*.address = "123 dsafkj ";*/
            /*.country_code = 32;*/
            /*.telephone = 324;*/
        /*};*/
    /*}*/
    {
        struct client new_client = {
            .name = "John"
        };
    }


}
