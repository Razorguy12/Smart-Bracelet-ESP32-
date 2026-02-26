from fastapi import FastAPI
from pydantic import BaseModel

app = FastAPI()


class ScanData(BaseModel):
    id: str
    product: str


@app.get("/")
def home():
    return {
        "message": "Smart Bracelet Server Running"
    }


@app.post("/test/scan")
def scan(data: ScanData):

    print("Scan Received")
    print("ID:", data.id)
    print("Product:", data.product)

    return {
        "status": "success",
        "message": "Scan received",
        "id": data.id,
        "product": data.product
    }