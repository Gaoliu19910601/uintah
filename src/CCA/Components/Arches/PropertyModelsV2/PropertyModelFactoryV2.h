#ifndef UT_PropertyModelFactoryV2_h
#define UT_PropertyModelFactoryV2_h

#include <CCA/Components/Arches/Task/TaskFactoryBase.h>
#include <string>

namespace Uintah{

  class PropertyModelFactoryV2 : public TaskFactoryBase {

  public:

    PropertyModelFactoryV2( );
    ~PropertyModelFactoryV2();

    void register_all_tasks( ProblemSpecP& db );

    void build_all_tasks( ProblemSpecP& db );

    std::vector<std::string> retrieve_task_subset( const std::string subset ) {

      if ( subset == "pre_update_property_models" ){

        return _pre_update_property_tasks;

      } else if ( subset == "pre_table_post_iv_update" ){

        return _pre_table_post_iv_update;

      } else if ( subset == "final_property_models" ){

        return _finalize_property_tasks;

      } else if ( subset == "variable_stat_models" ){

        return _var_stats_tasks;

      } else if ( subset == _all_tasks_str ){

        return _active_tasks;

      } else {

        throw InvalidValue("Error: Accessing the base class implementation of retrieve_task_subset in PropertyModelFactoryV2, which means there is no specific implementation for this factory.",__FILE__,__LINE__);

      }
    }

    void add_task( ProblemSpecP& db );

    void schedule_initialization( const LevelP& level,
                                  SchedulerP& sched,
                                  const MaterialSet* matls,
                                  bool doing_restart );

  protected:

  private:

    std::vector<std::string> _pre_update_property_tasks;  ///<Tasks that execute at the start of an RK step
    std::vector<std::string> _finalize_property_tasks;    ///<Tasks that execute at the end of the time step
    std::vector<std::string> _pre_table_post_iv_update;   ///<Tasks that execute after IV update and before table lookup
    std::vector<std::string> _var_stats_tasks;            ///<All Tasks associated with variable stats

    std::vector<std::string> _task_order;                 ///<The order in which these tasks should execute

    std::string m_vel_name;                               ///<Name of the task that creates all face velocities

  };
}
#endif
