// Datastructures.cc
//
// Student name:
// Student email:
// Student number:

#include "datastructures.hh"

#include <random>

#include <cmath>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    // Write any initialization you need here
}

Datastructures::~Datastructures()
{
    // Write any cleanup you need here
}

unsigned int Datastructures::get_affiliation_count()
{
    // Replace the line below with your implementation
    //    throw NotImplemented("get_affiliation_count()");
    return affiliations.size();
}

void Datastructures::clear_all()
{
    // Replace the line below with your implementation
    //    throw NotImplemented("clear_all()");
    affiliations.clear();
    publications.clear();
    sorted_names.clear();
}

std::vector<AffiliationID> Datastructures::get_all_affiliations()
{
    // Replace the line below with your implementation
    //    throw NotImplemented("get_all_affiliations()");
    std::vector<AffiliationID> v_a;
    for(std::unordered_map<AffiliationID, Affiliation>::iterator it = affiliations.begin(); it != affiliations.end(); ++it)
    {
        v_a.push_back(it->first);
    }
    return v_a;
}

bool Datastructures::add_affiliation(AffiliationID id, const Name & name, Coord xy)
{
    // Replace the line below with your implementation
    //    throw NotImplemented("add_affiliation()");
    sorted_state = false;
    std::unordered_map<AffiliationID, Affiliation>::iterator pos = affiliations.find(id);
    if(pos != affiliations.end()){
        return false;
    }
    else{
        Affiliation new_aff;
        new_aff.id_a = id;
        new_aff.name = name;
        new_aff.coord = xy;
        affiliations.insert(std::pair<AffiliationID, Affiliation>(id, new_aff));
        return true;
    }
}

Name Datastructures::get_affiliation_name(AffiliationID id)
{
    // Replace the line below with your implementation
    //    throw NotImplemented("get_affiliation_name()");
    std::unordered_map<AffiliationID, Affiliation>::iterator pos = affiliations.find(id);
    if(pos == affiliations.end()){
        return NO_NAME;
    }
    else{
        return (pos->second).name;
    }
}

Coord Datastructures::get_affiliation_coord(AffiliationID id)
{
    // Replace the line below with your implementation
    //    throw NotImplemented("get_affiliation_coord()");
    std::unordered_map<AffiliationID, Affiliation>::iterator pos = affiliations.find(id);
    if(pos == affiliations.end()){
        return NO_COORD;
    }
    else{
        return (pos->second).coord;
    }
}

std::vector<AffiliationID> Datastructures::get_affiliations_alphabetically()
{
    // Replace the line below with your implementation
    //    throw NotImplemented("get_affiliations_alphabetically()");
    //    std::vector<std::pair<AffiliationID, Affiliation>> v_pair;
    //    v_pair.reserve(affiliations.size());

    //    for(auto& pair:affiliations){
    //        v_pair.push_back(pair);
    //    }

    //    std::sort(v_pair.begin(), v_pair.end(), [](auto& l, auto& r){
    //        return l.second.name < r.second.name;
    //    });

    //    std::vector<AffiliationID> v_id;
    //    v_pair.reserve(affiliations.size());

    //    for(auto& pair:v_pair){
    //        v_id.push_back(pair.first);
    //    }

    //    return v_id;

    if (!sorted_state){
        std::vector<AffiliationID> v_id;
        v_id.reserve(affiliations.size());
        for(auto& pair : affiliations){
            v_id.push_back(pair.first);
        }

        std::sort(v_id.begin(), v_id.end(), [this](auto& l, auto& r){
            return affiliations[l].name < affiliations[r].name;
        });
        sorted_names = v_id;
        sorted_state = true;
    }
    return sorted_names;
}

std::vector<AffiliationID> Datastructures::get_affiliations_distance_increasing()
{
    // Replace the line below with your implementation
    //    throw NotImplemented("get_affiliations_distance_increasing()");

    //    std::vector<std::pair<AffiliationID, Affiliation>> v_pair;
    //    for(auto& pair:affiliations){
    //        v_pair.push_back(pair);
    //    }

    //    std::sort(v_pair.begin(), v_pair.end(), [](auto a, auto b){
    //        return sqrt(a.second.coord.x*a.second.coord.x + a.second.coord.y*a.second.coord.y) < sqrt(b.second.coord.x*b.second.coord.x + b.second.coord.y*b.second.coord.y);
    //    });

    //    std::vector<AffiliationID> v_id;
    //    for(std::vector<std::pair<AffiliationID, Affiliation>>::iterator it = v_pair.begin(); it != v_pair.end(); ++it){
    //        v_id.push_back((*it).first);
    //    }

    //    return v_id;

    std::vector<AffiliationID> v_id;
    v_id.reserve(affiliations.size());

    for(auto& pair : affiliations){
        v_id.push_back(pair.first);
    }

    std::sort(v_id.begin(), v_id.end(), [this](auto& l, auto& r){
        return sqrt(affiliations[l].coord.x*affiliations[l].coord.x +
                    affiliations[l].coord.y*affiliations[l].coord.y) <
               sqrt(affiliations[r].coord.x*affiliations[r].coord.x +
                    affiliations[r].coord.y*affiliations[r].coord.y);
    });

    return v_id;
}

AffiliationID Datastructures::find_affiliation_with_coord(Coord xy)
{
    // Replace the line below with your implementation
    //    throw NotImplemented("find_affiliation_with_coord()");
    std::unordered_map<AffiliationID, Affiliation>::iterator it;
    for(it = affiliations.begin(); it != affiliations.end(); ++it){
        if((it->second).coord == xy){
            break;
        }
    }

    if(it == affiliations.end()){
        return NO_AFFILIATION;
    }
    else{
        return it->first;
    }
}

bool Datastructures::change_affiliation_coord(AffiliationID id, Coord newcoord)
{
    // Replace the line below with your implementation
    //    throw NotImplemented("change_affiliation_coord()");
    std::unordered_map<AffiliationID, Affiliation>::iterator pos = affiliations.find(id);
    if(pos == affiliations.end()){
        return false;
    }
    else{
        (pos->second).coord = newcoord;
        return true;
    }
}

bool Datastructures::add_publication(PublicationID id, const Name & name, Year year, const std::vector<AffiliationID> & affiliations)
{
    // Replace the line below with your implementation
    //    throw NotImplemented("add_publication()");
    std::unordered_map<PublicationID, Publication>::iterator pos = publications.find(id);
    if(pos != publications.end()){
        return false;
    }
    else{
        Publication new_pub;
        new_pub.id_p = id;
        new_pub.title = name;
        new_pub.year = year;
        new_pub.affiliations = affiliations;
        publications.insert(std::pair<PublicationID, Publication>(id, new_pub));
        return true;
    }
}

std::vector<PublicationID> Datastructures::all_publications()
{
    // Replace the line below with your implementation
    //    throw NotImplemented("all_publications()");
    std::vector<PublicationID> v_p;
    for(std::unordered_map<PublicationID, Publication>::iterator it = publications.begin(); it != publications.end(); ++it){
        v_p.push_back(it->first);
    }
    return v_p;
}

Name Datastructures::get_publication_name(PublicationID id)
{
    // Replace the line below with your implementation
    //    throw NotImplemented("get_publication_name()");
    std::unordered_map<PublicationID, Publication>::iterator pos = publications.find(id);
    if(pos == publications.end()){
        return NO_NAME;
    }
    else{
        Name res = (pos->second).title;
        return res;
    }
}

Year Datastructures::get_publication_year(PublicationID id)
{
    // Replace the line below with your implementation
    //    throw NotImplemented("get_publication_year()");
    std::unordered_map<PublicationID, Publication>::iterator pos = publications.find(id);
    if(pos == publications.end()){
        return NO_YEAR;
    }
    else{
        Year res = (pos->second).year;
        return res;
    }
}

std::vector<AffiliationID> Datastructures::get_affiliations(PublicationID id)
{
    // Replace the line below with your implementation
    //    throw NotImplemented("get_affiliations()");
    std::unordered_map<PublicationID, Publication>::iterator pos = publications.find(id);
    std::vector<AffiliationID> v;
    if(pos == publications.end()){
        v.push_back(NO_AFFILIATION);
        return v;
    }
    else{
        v = (pos->second).affiliations;
        return v;
    }
}

bool Datastructures::add_reference(PublicationID id, PublicationID parentid)
{
    // Replace the line below with your implementation
    //    throw NotImplemented("add_reference()");
    std::unordered_map<PublicationID, Publication>::iterator pos1 = publications.find(id);
    std::unordered_map<PublicationID, Publication>::iterator pos2 = publications.find(parentid);
    if(pos1 == publications.end() || pos2 == publications.end()){
        return false;
    }
    else{
        std::unordered_map<PublicationID, std::vector<PublicationID>>::iterator pos = references.find(parentid);
        if(pos == references.end()){
            std::vector<PublicationID> v_r;
            v_r.push_back(id);
            references.insert(std::pair<PublicationID, std::vector<PublicationID>>(parentid, v_r));
        }
        else{
            references[parentid].push_back(id);
        }
        return true;
    }
}

std::vector<PublicationID> Datastructures::get_direct_references(PublicationID id)
{
    // Replace the line below with your implementation
    //    throw NotImplemented("get_direct_references()");
    std::unordered_map<PublicationID, std::vector<PublicationID>>::iterator pos = references.find(id);
    std::vector<PublicationID> v_res;
    if(pos == references.end()){
        return v_res;
    }
    else{
        v_res = pos->second;
        return v_res;
    }
}

bool Datastructures::add_affiliation_to_publication(AffiliationID affiliationid, PublicationID publicationid)
{
    // Replace the line below with your implementation
    //    throw NotImplemented("add_affiliation_to_publication()");
    std::unordered_map<AffiliationID, Affiliation>::iterator pos_a = affiliations.find(affiliationid);
    std::unordered_map<PublicationID, Publication>::iterator pos_p = publications.find(publicationid);

    if(pos_a == affiliations.end() || pos_p == publications.end()){
        return false;
    }
    else{
        (pos_p->second).affiliations.push_back(affiliationid);
        return true;
    }
}

std::vector<PublicationID> Datastructures::get_publications(AffiliationID id)
{
    // Replace the line below with your implementation
    //    throw NotImplemented("get_publications()");
    std::vector<PublicationID> v_res;

    std::vector<AffiliationID> v_a = get_all_affiliations();
    std::vector<AffiliationID>::iterator it = std::find(v_a.begin(), v_a.end(), id);
    if(it == v_a.end()){
        v_res.push_back(NO_PUBLICATION);
        return v_res;
    }

    for(std::unordered_map<PublicationID, Publication>::iterator it = publications.begin(); it != publications.end(); ++it){
        for(auto& e : (it->second).affiliations){
            if(e == id){
                v_res.push_back(it->first);
            }
        }
    }

    return v_res;
}

PublicationID Datastructures::get_parent(PublicationID id)
{
    // Replace the line below with your implementation
    //    throw NotImplemented("get_parent()");
    PublicationID id_res = 0;
    for(std::unordered_map<PublicationID, std::vector<PublicationID>>::iterator it = references.begin(); it != references.end(); ++it){
        for(auto& e : it->second){
            if(e == id){
                id_res = it->first;
                return id_res;
            }
        }

    }
    return NO_PUBLICATION;
}

std::vector<std::pair<Year, PublicationID> > Datastructures::get_publications_after(AffiliationID affiliationid, Year year)
{
    // Replace the line below with your implementation
    //    throw NotImplemented("get_publications_after()");
    std::vector<std::pair<Year, PublicationID>> v_res;

    std::vector<PublicationID> v = get_publications(affiliationid);
    if(v.empty() || v[0] == NO_PUBLICATION ){
        v_res.push_back(std::pair<Year, PublicationID>(NO_YEAR, NO_PUBLICATION));
    }
    else{
        for(auto& e1 : v){
            v_res.push_back(std::pair<Year, PublicationID>(get_publication_year(e1), e1));
        }

        auto new_end = std::remove_if(v_res.begin(), v_res.end(), [&year](auto e2){return e2.first < year;});
        v_res.erase(new_end, v_res.end());

        std::sort(v_res.begin(), v_res.end(), [](auto l, auto r){
            if(l.first < r.first){
                return true;
            }
            else if(l.first == r.first){
                return l.second < r.second;
            }
            return false;
        });
    }

    return v_res;
}

std::vector<PublicationID> Datastructures::get_referenced_by_chain(PublicationID id)
{
    // Replace the line below with your implementation
    //    throw NotImplemented("get_referenced_by_chain()");
    std::vector<PublicationID> v;

    std::vector<PublicationID> v_p = all_publications();
    auto it = std::find(v_p.begin(), v_p.end(), id);
    if(it == v_p.end()){
        v.push_back(NO_PUBLICATION);
        return v;
    }

    PublicationID parentid = get_parent(id);

    if(parentid == NO_PUBLICATION){
        return v;
    }

    v.push_back(parentid);

    std::vector<PublicationID> recurse_v = get_referenced_by_chain(parentid);
    for(auto& e : recurse_v){
        v.push_back(e);
    }

    return v;
}

std::vector<PublicationID> Datastructures::get_all_references(PublicationID id)
{
    // Replace the line below with your implementation
    //    throw NotImplemented("get_all_references()");
    std::vector<PublicationID> v;

    std::vector<PublicationID> v_p = all_publications();
    auto it = std::find(v_p.begin(), v_p.end(), id);
    if(it == v_p.end()){
        v.push_back(NO_PUBLICATION);
        return v;
    }

    for(auto& pair : references){
        if(pair.first == id){
            for(auto& e1 : pair.second){
                v.push_back(e1);
                std::vector<PublicationID> v_recurse = get_all_references(e1);
                for(auto& e2 : v_recurse){
                    v.push_back(e2);
                }
            }
        }
    }

    return v;
}

std::vector<AffiliationID> Datastructures::get_affiliations_closest_to(Coord xy)
{
    // Replace the line below with your implementation
    //    throw NotImplemented("get_affiliations_closest_to()");
    std::vector<std::pair<AffiliationID, Affiliation>> v_pair;
    for(auto& pair:affiliations){
        v_pair.push_back(pair);
    }

    std::sort(v_pair.begin(), v_pair.end(), [xy](auto a, auto b){
        return sqrt((a.second.coord.x-xy.x)*(a.second.coord.x-xy.x) + (a.second.coord.y-xy.y)*(a.second.coord.y-xy.y)) < sqrt((b.second.coord.x-xy.x)*(b.second.coord.x-xy.x) + (b.second.coord.y-xy.y)*(b.second.coord.y-xy.y));
    });

    std::vector<AffiliationID> v_id;
    for(auto& e : v_pair){
        v_id.push_back(e.first);
    }

    if(v_id.size() <= 3){
        return v_id;
    }

    std::vector<AffiliationID> v_res;
    v_res.push_back(v_id[0]);
    v_res.push_back(v_id[1]);
    v_res.push_back(v_id[2]);
    return v_res;
}

bool Datastructures::remove_affiliation(AffiliationID id)
{
    // Replace the line below with your implementation
    //    throw NotImplemented("remove_affiliation()");
    auto pos = affiliations.find(id);
    if(pos == affiliations.end()){
        return false;
    }

    affiliations.erase(pos);
    for(auto& e : publications){
        auto pos_p = std::find(e.second.affiliations.begin(), e.second.affiliations.end(), id);
        if(pos_p != e.second.affiliations.end()){
            e.second.affiliations.erase(pos_p);
        }
    }

    return true;
}

PublicationID Datastructures::get_closest_common_parent(PublicationID id1, PublicationID id2)
{
    // Replace the line below with your implementation
    //    throw NotImplemented("get_closest_common_parent()");
    if(publications.find(id1) == publications.end() || publications.find(id2) == publications.end()){
        return NO_PUBLICATION;
    }

    std::vector<PublicationID> chain1 = get_referenced_by_chain(id1);
    std::vector<PublicationID> chain2 = get_referenced_by_chain(id2);

    for(auto& e : chain2){
        std::vector<PublicationID>::iterator pos = std::find(chain1.begin(), chain1.end(), e);
        if(pos != chain1.end()){
            return *pos;
        }
    }

    return NO_PUBLICATION;
}

bool Datastructures::remove_publication(PublicationID publicationid)
{
    // Replace the line below with your implementation
    //    throw NotImplemented("remove_publication()");
    auto pos = publications.find(publicationid);
    if(pos == publications.end()){
        return false;
    }

    publications.erase(pos);

    auto pos_r = references.find(publicationid);
    if(pos_r != references.end()){
        references.erase(pos_r);
    }

    for(auto& e : references){
        std::vector<PublicationID>::iterator it = std::find(e.second.begin(), e.second.end(), publicationid);
        if(it != e.second.end()){
            e.second.erase(it);
        }
    }

    return true;
}



