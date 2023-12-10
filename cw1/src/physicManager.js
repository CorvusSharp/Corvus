import {mapManager} from "./mapManager.js";
import {gameManager} from "./gameManager.js";

class PhysicManager {
    update(obj, level) {

        if (obj.type === 'Player' && obj.health <= 0) {
            obj.die();
            gameManager.checkPlayerHealth();
            return "stop";
        }
        if (obj.move_x === 0 && obj.move_y === 0) {
            return "stop"; // скорости движения нулевые
        }

        let stepX = obj.move_x * obj.speed * level / 1.2;
        let stepY = obj.move_y * obj.speed * level / 1.2;

        // Разбиваем движение на более мелкие шаги
        let steps = Math.max(Math.abs(stepX), Math.abs(stepY));
        let deltaX = stepX / steps;
        let deltaY = stepY / steps;

        for (let i = 0; i < steps; i++) {
            let newX = obj.pos_x + deltaX;
            let newY = obj.pos_y + deltaY;

            if (!this.hasCollision(obj, newX, newY)) {
                // Если столкновения нет, обновляем позицию
                obj.pos_x = newX;
                obj.pos_y = newY;
            } else {
                return "break"; // дальше двигаться нельзя
            }
        }

        return "move"; // двигаемся
    }


    hasCollision(obj, newX, newY) {
        let passableTile = 152;
        // Вычисляем центральные точки новой позиции объекта
        let centerX = newX + obj.size_x / 2;
        let centerY = newY + obj.size_y / 2;

        // Проверка столкновений с тайлами
        let tileIndex = mapManager.getTilesetIdx(centerX, centerY);
        if (tileIndex !== passableTile) {
            return true; // Обнаружено столкновение с тайлом
        }

        // Проверка столкновений с другими сущностями
        for (let other of gameManager.entities) {
            // Пропускаем проверку, если взаимодействие не между врагом и игроком
            if (obj.type === 'Enemy' && other.type !== 'Player') continue;
            if (other.type === 'Enemy' && obj.type !== 'Player') continue;

            let otherCenterX = other.pos_x + other.size_x / 2;
            let otherCenterY = other.pos_y + other.size_y / 2;

            let distance = Math.sqrt(Math.pow(centerX - otherCenterX, 2) + Math.pow(centerY - otherCenterY, 2));

            if (other !== obj && distance < obj.attackRange + other.size_x / 2) {
                obj.onTouchEntity(other);

                if (other.type === 'Enemy' && obj.type === 'Player' && obj.attacking) {
                    other.health -= obj.damage;
                    if (other.health <= 0) {
                        other.die();
                        gameManager.increaseKillCount();
                    }
                }
                return false;
            }
        }
        return false;
    }
}

export const physicManager = new PhysicManager();
