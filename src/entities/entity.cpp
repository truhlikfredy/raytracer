/*
 * author: Anton Krug anton.krug@gmail.com
 * date: 12/01/2018
 */

#include "entity.h"

Entity::Entity(Vector3 centerInit): center(centerInit) {
}

Entity::Entity(): center(Vector3()) {
}

#ifdef AABB
Entity::Entity(Vector3 centerInit, Vector3 aabbMinInit, Vector3 aabbMaxInit): center(centerInit), aabbMin(aabbMinInit), aabbMax(aabbMaxInit) {
}
#endif

