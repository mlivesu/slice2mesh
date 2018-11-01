#include "plc_cleanup.h"
#include "common.h"

using namespace cinolib;

void cleanup_plc(Trimesh<> & plc, const float min_len)
{
    plc.edge_unmark_all();

    double min_area = 0.05 * (plc.mesh_area()/static_cast<double>(plc.num_polys()));

    std::vector<uint> to_collapse;
    for(uint pid=0; pid<plc.num_polys(); ++pid)
    {
        int l = plc.poly_data(pid).label;
        if(l==SRF_FACE_DOWN || l==SRF_FACE_UP)
        {
            bool isolated = true;
            for(uint nbr : plc.adj_p2p(pid))
            {
                if(plc.poly_data(nbr).label==l) isolated = false;
            }
            if(isolated && plc.poly_area(pid)<min_area)
            {
                uint   e   = plc.adj_p2e(pid).front();
                double len = plc.edge_length(e);

                for(uint i=1; i<plc.adj_p2e(pid).size(); ++i)
                {
                    uint   ei   = plc.adj_p2e(pid).at(i);
                    double leni = plc.edge_length(ei);
                    if(leni<len)
                    {
                        e = ei;
                        leni = len;
                    }
                }
                to_collapse.push_back(e);
            }
        }
    }

    std::cout << to_collapse.size() << " tiny edges should be collapsed" << std::endl;
    SORT_VEC(to_collapse, true);
    uint count=0;
    for(uint eid : to_collapse) plc.edge_data(eid).marked = true; //if(plc.edge_collapse(eid,0)>=0) ++count;
    std::cout << count << " of them were actually collapsed" << std::endl;

//    bool collapsed_something = false;
//    do
//    {
//        std::vector<uint> to_collapse;
//        for(uint eid=0; eid<plc.num_edges(); ++eid)
//        {
//            if(plc.edge_valence(eid)==2)
//            {
//                uint pid0 = plc.adj_e2p(eid).front();
//                uint pid1 = plc.adj_e2p(eid).back();
//                int  l0   = plc.poly_data(pid0).label;
//                int  l1   = plc.poly_data(pid1).label;

//                bool collapsible = false;
//                if(l0==SRF_FACE_DOWN && l1==SRF_FACE_VERT) collapsible = true;
//                if(l0==SRF_FACE_VERT && l1==SRF_FACE_DOWN) collapsible = true;
//                if(l0==SRF_FACE_UP   && l1==SRF_FACE_VERT) collapsible = true;
//                if(l0==SRF_FACE_VERT && l1==SRF_FACE_UP  ) collapsible = true;
//                if(l0==SRF_FACE_DOWN && l1==SRF_FACE_DOWN) collapsible = true;
//                if(l0==SRF_FACE_UP   && l1==SRF_FACE_UP  ) collapsible = true;

//                if(collapsible && plc.edge_length(eid)<min_len) to_collapse.push_back(eid);
//            }
//        }

//        std::cout << to_collapse.size() << " tiny edges should be collapsed" << std::endl;
//        SORT_VEC(to_collapse, true);
//        uint count=0;
//        for(uint eid : to_collapse)  plc.edge_data(eid).marked = true; //if(plc.edge_collapse(eid,0)>=0) ++count;
//        std::cout << count << " of them were actually collapsed" << std::endl;

////        collapsed_something = count>0;
//    }
//    while(collapsed_something);
}
