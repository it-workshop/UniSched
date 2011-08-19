#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <vector>
#include <string>

#include <types.h>
#include <group.h>

using std::vector;
using std::string;

/** @class Queue
 * @brief Class keeps queue groups.
 */
class Queue {
private:
    id_type id_;				/**< Id of a queue. */
    string name_;				/**< Name of a queue. */
    vector<Group *> groups_;			/**< Vector of groups. */
public:
    Queue(id_type id, string name);		/**< Constructor.
						 * @param [in] id ID of queue.
						 * @param [in] name Name of queue.
						 */
    ~Queue();					/**< Destructor. */

    vector<Group *> *get_vector();		/**< Get b of a queue.
						 * @return Begin of a queue.
						 */
    id_type get_id();				/**< Get id of a queue.
						 * @return ID of a queue.
						 */
    void set_id(id_type id);			/**< Set id of a queue.
						 * @param [in] id New id.
						 */
    string get_name();				/**< Get name of a queue.
						 * @return Name of a queue.
						 */
    void enqueue(Group *adding);		/**< Push to queue.
						 * @param [in] adding Group to add.
						 */
    Group *dequeue();				/**< Pop from queue.
						 * @return Popped group.
						 */
};

#endif /* _QUEUE_H_ */

