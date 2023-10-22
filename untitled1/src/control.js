export default class Control {
    constructor(tetris, view) {
        this.renderFlagView = false;
        this.tetris = tetris;
        this.view = view;
        this.isPlay = false;
        this.interval = null;
        this.pauseFlag = false;
        this.startScreenFlag = true;
        document.addEventListener('keydown', this.handlKeydown.bind(this));
        document.addEventListener('keyup', this.handlKeyUp.bind(this));
        this.view.renderStartScreen();

        this.interval = setInterval(() => {
            if (this.isPlay)
                this.update();
        }, 1000);
    }




    reset() {
        document.getElementById('table').style.display = 'none';
        this.renderFlagView = false;
        this.view.renderStartScreen();
        this.tetris.resetPlayfield();
        this.isPlay = false;
        this.startScreenFlag = true;
        this.pauseFlag = false;
        this.stopTimer();
    }


    endSave() {
        const leaderboardTableBody = document.getElementById('table').querySelector('tbody');
        const username = localStorage.getItem("tetris.username");
        const score = tetris.score;
        let results = JSON.parse(localStorage.getItem("tetris.results")) || [];
        const result = {
            username: username,
            score: score
        }
        console.log(result)
        results.push(result);
        results.sort((a, b) => b.score - a.score);
        results = results.filter(result => result.username != null && result.score != null);
        results = results.filter((result, index, self) =>
            index === self.findIndex((t) => (
                t.username === result.username))
        );

        // Ограничиваем количество результатов до 8
        results = results.slice(0, 8);

        localStorage.setItem("tetris.results", JSON.stringify(results));
        leaderboardTableBody.innerHTML = '';
        function addOrUpdateLeaderboard(name, score) {
            console.log(score)
            const newRow = document.createElement('tr');
            const nameCell = document.createElement('td');
            nameCell.textContent = name;
            const scoreCell = document.createElement('td');
            scoreCell.textContent = score;

            newRow.appendChild(nameCell);
            newRow.appendChild(scoreCell);
            leaderboardTableBody.appendChild(newRow);
        }
        results.forEach(result => addOrUpdateLeaderboard(result.username, result.score));
    }


    renderView() {
        if (this.renderFlagView === true)
            return;
        const state = this.tetris.getState();
        if (!this.isPlay) {
            this.view.renderPauseScreen();
        }
        if (state.isGameOver) {
            this.view.renderEndScreen(state);
            document.getElementById('table').style.display = 'block';
            document.getElementById('top-link').style.display = 'block';
            document.getElementById('leaderboard-container').style.display = 'block';
            this.renderFlagView = true;
            this.endSave();
        }else{
            this.view.render(state);
        }
    }



    pauseGame() {
        this.pauseFlag = true;
        this.isPlay = false;
        this.view.renderPauseScreen();
        this.stopTimer();
    }

    playGame() {
        this.isPlay = true;
        this.pauseFlag = false;
        this.startScreenFlag = false;
        this.startTimer();
    }
    update() {
        this.tetris.movePieceDown();
        this.renderView();
    }
    startTimer() {
        const speed = 1000 - this.tetris.getState().level * 100;

        if (!this.interval) {
            this.interval = setInterval(() => {
                this.update();
            }, speed > 0 ? speed : 100);
        }
    }

    stopTimer() {
        if (this.interval) {
            clearInterval(this.interval);
            this.interval = null;
        }
    }



    handlKeydown(event) {
        switch (event.keyCode) {
            case 37: // LEFT
                this.isPlay = true;
                this.tetris.moveLeft();
                this.renderView();
                break;
            case 38: // UP
                this.isPlay = true;
                this.tetris.rotatePiece();
                this.renderView();
                break;
            case 39: // RIGHT
                this.isPlay = true;
                this.tetris.moveRight();
                this.renderView();
                break;
            case 40: // DOWN
                this.stopTimer();
                this.isPlay = true;
                this.tetris.moveDown();
                this.renderView();
                break;
            case 13: // ENTER
                this.playGame();
                break;
            case 27: // ESC
                if (this.pauseFlag === false && this.startScreenFlag === false)
                    this.pauseGame();
                break;
            case 82:
                document.getElementById('table').style.display = 'none';
                document.getElementById('top-link').style.display = 'none';
                document.getElementById('leaderboard-container').style.display = 'none';
                    this.reset();

                break;
            case 32: // SPACE
                this.tetris.fastDrop();
                this.renderView();
                break;
            default:
                break;
        }
    }
    handlKeyUp(event) {
        switch (event.keyCode) {
            case 40: // DOWN
                this.startTimer();
                break;
            default:
                break;
        }
    }
}