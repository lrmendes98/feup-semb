import {Button} from 'react-bootstrap';
import React from 'react';
import axios from 'axios';
import './ButtonComponent.css';

class LedComponent extends React.Component {
    constructor(props) {
        super(props)
        this.id = props.id;
        this.state = {
            on: false
        }
    }

    componentDidMount() {
        const url = `http://localhost:8081/led/${this.id}` 
        let currentComponent = this;
        this.interval = setInterval(() => {
            axios.get(url)
            .then(function (response) {
                currentComponent.setState({ on: response.data });
            })
            .catch(function (error) {
                console.log(error);
            });
        }, 500);
        
    }

    componentWillUnmount() {
        clearInterval(this.interval);
    }
    
    render() {
        return <div className="container">
            <Button className="button" variant={this.state.on ? "success" : "dark"} size="sm" disabled>Led {this.id}</Button>
        </div>
    }
}

export default LedComponent;