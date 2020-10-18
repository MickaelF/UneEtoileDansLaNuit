# Input Handling 

## How inputs are handled?
A Json file is created, with the wanted actions, for the wanted context (UI, a specific phase of gameplay, etc...). Each actions has a type. Each actions has corresponding bindings.



## Possible action type
- button: three states (pressed, released, held).
- axis: a gamepad axis, or a compond of two button. Result is a way between -1 (left or down) and 1 (up or right).
- 2DVector: A 2D vector, for 2 axis at a time. 



## Binding field 
A binding always has a related action. It can be composite or not, depending of binding and action's type. Only 'axis' and '2DVector' action type can be composite. 'Device' must be specified. 'Values' is the array with the GLFW key id of the binding. For 'gamepad' devices, binding type must be specified.
    
### Device type
Keyboard, Gamepad or Mouse. If it is for a specific gamepad, type must be "gamepad/{name}".
### Composite rules
For a 2D vector, four buttons or two axis corresponding to "up/down" and "left/right" must be specified. For an 'axis', two buttons or one axis.
### Binding types (for gamepad only)
For anything that can have a value inbetween a range (sticks and triggers), type must be "range". Otherwise, it should be "button".


## JSON example
    {
        "maps": 
        [
            {
                "name":"UI",
                "actions": 
                [
                    {
                        "name":"Submit", 
                        "valueType":"Button"
                    },
                    { 
                        "name":"Move", 
                        "valueType":"2DVector"
                    }, 
                    { 
                        "name":"Cancel", 
                        "valueType": "Button"
                    }
                ] , 
                "bindings": 
                [
                    {
                        "action":"Move", 
                        "name":"Arrows",
                        "isComposite":true, 
                        "device":"keyboard",
                        "values":[265,264,263,262]
                    }, 
                    {
                        "action":"Move", 
                        "name":"WASD",
                        "isComposite":true, 
                        "device":"keyboard",
                        "values":[87,83,65,68]
                    },
                    {
                        "action":"Move", 
                        "name":"Left stick",
                        "isComposite":true,
                        "device":"gamepad",
                        "type":"axis",
                        "values":[1,0]
                    }
                ]
            }
        ]
    }