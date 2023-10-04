export default class Control {
    constructor(tetris, view) {
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
        this.view.renderStartScreen();
        this.tetris.resetPlayfield();
        this.isPlay = false;
        this.startScreenFlag = true;
        this.pauseFlag = false;
        this.stopTimer();
    }

    renderView() {
        const state = this.tetris.getState();
        if (!this.isPlay) {
            this.view.renderPauseScreen();
        }
        if (state.isGameOver) {
            this.view.renderEndScreen(state.score);
        }else{
            this.view.render(state);
        }
    }


    restart
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
        this.renderView();
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
                this.tetris.movePieceLeft();
                this.renderView();
                break;
            case 38: // UP
                this.isPlay = true;
                this.tetris.rotatePiece();
                this.renderView();
                break;
            case 39: // RIGHT
                this.isPlay = true;
                this.tetris.movePieceRight();
                this.renderView();
                break;
            case 40: // DOWN
                this.stopTimer();
                this.isPlay = true;
                this.tetris.movePieceDown();
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
                if(this.startScreenFlag === false && this.pauseFlag === false)
                    this.reset();
                break;
            case 32: // SPACE
                this.tetris.fastDrop();
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