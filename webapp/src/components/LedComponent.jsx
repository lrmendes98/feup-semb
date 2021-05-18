import {Button} from 'react-bootstrap';
import React from 'react';
import './ButtonComponent.css';

class LedComponent extends React.Component {
    constructor(props) {
        super(props)
        this.id = props.id;
        this.state = {
            on: false
        }
    }
    
    render() {
        return <div className="container">
            <Button className="button" variant={this.state.on ? "success" : "dark"} size="sm" disabled>Led {this.id}</Button>
        </div>
    }
}

export default LedComponent;