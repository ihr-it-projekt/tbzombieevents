modded class ZombieBase {
    vector attackPosition;
    int maxRadius;

    bool CanAttackPlayer(vector playerPos) {
        if(!attackPosition || !maxRadius) {
            return true;
        }

        if(!IsAlive()) {
            return false;
        }

        float distance = vector.Distance(attackPosition, playerPos);

        return distance < maxRadius;
    }
}