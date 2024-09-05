pipeline {
    agent any

    stages {


        stage('Build') {
            steps {
                // Example build step
                echo 'Building...'
                // Run shell commands within the sh block
                sh '''
                    cd algo-trading
                    ./run-build.sh
                '''
            }
        }
    }
}