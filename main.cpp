#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

class transport {
    public:
        int getBuildingId1() const{
            return this ->_buildingId1;
        };

        int getBuildingId2() const{
            return this->_buildingId2;
        };

        string getType() const{
            return this->_type;
        };

        int getCapacity() const{
            return this->_capacity;
        };

        transport(){};
        transport( int capacity, int begin, int end) : _capacity(capacity), _buildingId1(begin), _buildingId2(end){
            if (capacity == 0)
                this->_type = "teleporteur";
            else
                this->_type = "tube";
        };

    private:
        int     _capacity;
        string  _type;
        int     _buildingId1;
        int     _buildingId2;
};

class pods {
    public:
        int getPodId() const {
            return this->_podId;
        };

        string getPodProprerties() const {
            return this->_pod_properties;
        }

        void setPodId( string pod_properties ) {
            istringstream iss(pod_properties);
            int firstNumber;
            iss >> firstNumber;
            this->_podId = firstNumber;
        };

        void setRoad( string pod_properties ) {
            istringstream iss(pod_properties);
            string restOfString;
            getline(iss, restOfString);
            this->_road = restOfString;
        };

        pods(){};
        pods(string pod_properties) : _pod_properties(pod_properties) {};
        pods (int podId, int numStops) : _podId(podId), _numStops(numStops){};
    private:
        string _pod_properties;
        int _podId;
        int _numStops;
        string _road;
};

class SeleniaCity : public transport, public pods {
    public:
        int getNumPods () {
            return this->_numPods;
        };

        int getNumTravelRoute() {
            return this->_numTravelRoute;
        };
        void setResource( unsigned int resource ) {
            this->_resource = resource;
        };

        void setNumPods( int numPods) {
            this->_numPods = numPods;
        };

        void setNumTravelRoute (int numTravelRoute) {
            this->_numTravelRoute = numTravelRoute;
        };

        void setArrayTransport(int capacity, int begin, int end) {
            this->_arrayTransport.push_back(transport(capacity, begin, end));
        };

        void setArrayPods( string pod_properties ) {
            this->_arrayPods.push_back(pods(pod_properties));
        };


        void printData() {
            cerr << "vous avez " << this->_resource << " ressources" << endl;
            cerr << "il y a actuellement " << this->_numTravelRoute << " lignes de transport" << endl;
            for (const auto& transport : _arrayTransport) {
                if (transport.getType() == "tube")
                    cerr << "un tube de capacite " << transport.getCapacity() << " entre les batiments " << transport.getBuildingId1() << " et " << transport.getBuildingId2() << endl;
                else
                    cerr << "un teleporteur du batiement " << transport.getBuildingId1() << " au " << transport.getBuildingId2() << endl;
            }
            cerr << "il y a actuellement " << this->_numPods << " capsule de transport" << endl;
            for (const auto& pods : _arrayPods) {
                cerr << "Capsule " << pods.getPodId() << " avec l'itineraire " << pods.getPodProprerties() << endl;
            }
        };

        SeleniaCity(){}
    
    private:
        int                     _numPods;
        int                     _numTravelRoute;
        unsigned int            _resource;
        vector<transport>  _arrayTransport;
        vector<pods>       _arrayPods;
};


int main()
{

    // game loop
    SeleniaCity city;
    while (1) {
        int resources;
        cin >> resources; cin.ignore();
        city.setResource(resources);
        int num_travel_routes;
        cin >> num_travel_routes; cin.ignore();
        city.setNumTravelRoute(num_travel_routes);
        for (int i = 0; i < num_travel_routes; i++) {
            int building_id_1;
            int building_id_2;
            int capacity;
            cin >> building_id_1 >> building_id_2 >> capacity; cin.ignore();
            city.setArrayTransport(capacity, building_id_1, building_id_2);
        }
        int num_pods;
        cin >> num_pods; cin.ignore();
        city.setNumPods(num_pods);
        for (int i = 0; i < num_pods; i++) {
            string pod_properties;
            getline(cin, pod_properties);
            city.setArrayPods(pod_properties);
        }
        int num_new_buildings;
        cin >> num_new_buildings; cin.ignore();
        for (int i = 0; i < num_new_buildings; i++) {
            string building_properties;
            getline(cin, building_properties);
        }
        city.printData();
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        cout << "TUBE 0 1;TUBE 0 2; POD 42 0 1 0 2 0 1 0 2" << endl; // TUBE | UPGRADE | TELEPORT | POD | DESTROY | WAIT
    }
}