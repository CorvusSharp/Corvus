const gulp = require('gulp');
const deleteAsync = require('del').deleteAsync;
const babel = require('gulp-babel');
const gulpSass = require('gulp-sass');
const cleanCSS = require('gulp-clean-css');
const sassCompiler = require('node-sass');
const uglify = require('gulp-uglify');
const sass = gulpSass(sassCompiler);

function clean() {
    return deleteAsync(['gulpBuild']);
}

function js() {
    return gulp.src('public/javascripts/**/*.js')
        .pipe(babel({
            presets: ['@babel/preset-env']
        }))
        .pipe(uglify())
        .pipe(gulp.dest('gulpBuild/javascripts'));
}

function styles() {
    return gulp.src('public/stylesheets/**/*.sass')
        .pipe(sass())
        .pipe(cleanCSS())
        .pipe(gulp.dest('gulpBuild/stylesheets'));
}

function watch() {
    gulp.watch('public/stylesheets/**/*.sass', styles);
    gulp.watch('public/javascripts/**/*.js', js);
}

const build = gulp.series(clean, gulp.parallel(styles, js));

module.exports = {
    clean,
    js,
    styles,
    watch,
    default: build
};

